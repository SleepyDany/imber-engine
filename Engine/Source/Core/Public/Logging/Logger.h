// Copyright ImberEngine. All rights reserved.
#pragma once

#include "Core/Public/Types/BaseTypes.h"
#include "CoreDefinitions.h"
#include "LogSubsystem.h"
#include "LogVerbosity.h"

#include <format>
#include <memory>
#include <vector>

namespace Imber::Logging
{
	class ILogSink;

	class LoggerBase
	{
	public:
		LoggerBase(const std::string& name,
			ELogVerbosity::Type defaultVerbosity,
			ELogVerbosity::Type maxVerbosity,
			const std::vector<std::shared_ptr<ILogSink>>& sinks);
		virtual ~LoggerBase();

		inline std::string GetName() const
		{
			return Name;
		}
		inline ELogVerbosity::Type GetCurrentVerbosity() const
		{
			return CurrentVerbosity;
		}
		inline ELogVerbosity::Type GetDefaultVerbosity() const
		{
			return DefaultVerbosity;
		}
		inline constexpr ELogVerbosity::Type GetMaxVerbosity() const
		{
			return MaxVerbosity;
		}

		void SetCurrentVerbosity(ELogVerbosity::Type newVerbosity);

	protected:
		inline std::vector<std::string> GetSinkNames() const;

	private:
		void ResetToDefaultVerbosity();

		std::string Name;
		ELogVerbosity::Type CurrentVerbosity;
		const ELogVerbosity::Type DefaultVerbosity;
		const ELogVerbosity::Type MaxVerbosity;

		std::vector<std::weak_ptr<ILogSink>> Sinks;
		std::vector<std::string> SinkNames;
	};

	template <ELogVerbosity::Type InDefaultVerbosity, ELogVerbosity::Type InMaxVerbosity>
	class Logger : public LoggerBase
	{
	public:
		Logger(const std::string& name,
			ELogVerbosity::Type defaultVerbosity,
			ELogVerbosity::Type maxVerbosity,
			const std::vector<std::shared_ptr<ILogSink>>& sinks = {}) // TODO: add default sinks
			: LoggerBase(name, InDefaultVerbosity, InMaxVerbosity, sinks)
		{
		}

		inline constexpr ELogVerbosity::Type GetMaxVerbosity() const
		{
			return InMaxVerbosity;
		}

		template <class... Args>
		void Log(const ELogVerbosity::Type& verbosity,
			const std::string& file,
			const std::string& function,
			int32 line,
			const std::string& message,
			Args&&... arguments)
		{
			LogContext Context(GetName(),
				std::format(message, std::forward<Args>(arguments)...),
				file,
				function,
				line,
				verbosity,
				std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now()),
				GetSinkNames());

			if (const auto LogSubsystem = LogSubsystem::Get())
			{
				LogSubsystem->PushLog(Context);
			}
		}
	};

} // namespace Imber::Logging
