#include "Public/Logging/Sinks/ConsoleLogSink.h"

#include "Public/Logging/LogVerbosity.h"

#include <chrono>
#include <format>
#include <iostream>

namespace Imber::Logging
{
	ConsoleLogSink::ConsoleLogSink(const std::string& name) : ILogSink(name)
	{
	}

	void ConsoleLogSink::Sink(const LogContext& context)
	{
		std::unique_lock<std::mutex> LockStream(Mutex);
		std::cout << Format(context) << '\n';
	}

	std::string ConsoleLogSink::Format(const LogContext& context)
	{
		// TODO: Customize with named formatter
		return std::format("[{:%F %T}]\t{}: {:<7}\t{}\t[{}:{}:{}]",
			context.Timestamp,
			context.LoggerName,
			ELogVerbosity::ToString(context.LoggerVerbosity),
			context.Message,
			context.File,
			context.Function,
			context.Line);
	}

} // namespace Imber::Logging