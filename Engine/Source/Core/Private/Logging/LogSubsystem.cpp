// Copyright ImberEngine. All rights reserved.
#include "Public/Logging/LogSubsystem.h"

#include "Public/Logging/Logger.h"
#include "Public/Logging/Sinks/ConsoleLogSink.h"
#include "Public/Logging/Sinks/LogSink.h"

#include <cassert>

namespace Imber::Logging
{
	std::shared_ptr<LogSubsystem> LogSubsystem::Get()
	{
		static std::shared_ptr<LogSubsystem> Instance = std::make_shared<LogSubsystem>(); // TODO: Customize with settings
		return Instance;
	}

	LogSubsystem::~LogSubsystem()
	{
		if (bRunning)
		{
			Shutdown();
		}
	}

	void LogSubsystem::Initialize()
	{
		bRunning = true;
		LogThread = std::thread(&LogSubsystem::ProcessLog, this);

		RegisterSink(std::make_shared<ConsoleLogSink>("DefaultConsoleLogSink"));
		// RegisterSink(std::make_shared<RotatingFileSink>());
	}

	void LogSubsystem::Shutdown()
	{
		bRunning = false;
		LogCondition.notify_one();
		if (LogThread.joinable())
		{
			LogThread.join();
		}

		SinkMap.clear();
	}

	void LogSubsystem::RegisterSink(const std::shared_ptr<ILogSink>& sink)
	{
		assert(sink != nullptr /*, "Unable to register sink: Sink is null"*/);

		{
			std::unique_lock<std::mutex> LockSink(SinkMutex);
			SinkMap.try_emplace(sink->GetName(), sink);
		}
	}

	void LogSubsystem::PushLog(const LogContext& context)
	{
		// LogQueue.Push(context);
		std::unique_lock<std::mutex> LockQueue(LogMutex);
		LogQueue.push(context);
		LogCondition.notify_one();
	}

	void LogSubsystem::ProcessLog()
	{
		while (bRunning)
		{
			std::unique_lock<std::mutex> LockQueue(LogMutex);
			LogCondition.wait(LockQueue, [this] { return !LogQueue.empty() || !bRunning; });

			// TODO: What to do if bRunning = false, but LogQueue.size() > 1 ???
			if (!bRunning && LogQueue.empty())
			{
				break;
			}

			LogContext Context = LogQueue.front();
			LogQueue.pop();
			LockQueue.unlock();

			std::unique_lock<std::mutex> LockSink(SinkMutex);
			for (auto& SinkName : Context.SinkNames)
			{
				const auto SinkIter = SinkMap.find(SinkName);
				if (SinkIter != SinkMap.end() && SinkIter->second != nullptr)
				{
					SinkIter->second->Sink(Context);
				}
			}
		}
	}

} // namespace Imber::Logging