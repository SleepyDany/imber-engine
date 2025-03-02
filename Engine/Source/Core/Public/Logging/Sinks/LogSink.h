#pragma once

#include "Public/Logging/Logger.h"

#include <mutex>
#include <string>

namespace Imber::Logging
{
	struct LogContext;

	class ILogSink
	{
	public:
		ILogSink() = delete;
		ILogSink(const std::string& name);
		virtual ~ILogSink() = default;

		inline std::string GetName() const
		{
			return Name;
		}
		virtual void Sink(const LogContext& context) = 0;
		virtual std::string Format(const LogContext& context) = 0;

	protected:
		std::string Name;
		std::mutex Mutex;
	};

} // namespace Imber::Logging
