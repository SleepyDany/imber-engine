#pragma once

#include "LogSink.h"

namespace Imber::Logging
{
	struct LogContext;

	class ConsoleLogSink : public ILogSink
	{
	public:
		ConsoleLogSink() = delete;
		ConsoleLogSink(const std::string& name);
		virtual ~ConsoleLogSink() override = default;

		virtual void Sink(const LogContext& context) override;
		virtual std::string Format(const LogContext& context) override;
	};

} // namespace Imber::Logging
