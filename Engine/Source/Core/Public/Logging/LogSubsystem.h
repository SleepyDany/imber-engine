// Copyright ImberEngine. All rights reserved.
#pragma once

#include "CoreDefinitions.h"
#include "LogVerbosity.h"

#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>
// #include <vector>

namespace Imber::Logging
{
	class ILogSink;

	class LogSubsystem // TODO : public Imber::ISubsystem
	{
		friend class std::_Ref_count_base;

	public:
		static std::shared_ptr<LogSubsystem> Get();

		// TODO: customize with settings
		// TODO: make private (resolve access for shared_ptr problems)
		LogSubsystem() = default;
		LogSubsystem(const LogSubsystem&) = delete;
		LogSubsystem(LogSubsystem&&) = delete;
		LogSubsystem& operator=(const LogSubsystem&) = delete;
		LogSubsystem& operator=(LogSubsystem&&) = delete;
		~LogSubsystem();

		void Initialize();
		void Shutdown();

		void RegisterSink(const std::shared_ptr<ILogSink>& sink);

		void PushLog(const LogContext& context);

	private:
		void ProcessLog();

		std::mutex LogMutex;
		std::mutex SinkMutex;
		std::condition_variable LogCondition;
		std::thread LogThread;
		bool bRunning = true;
		std::queue<LogContext> LogQueue;

		std::unordered_map<std::string /*SinkName*/, std::shared_ptr<ILogSink>> SinkMap;
	};

} // namespace Imber::Logging