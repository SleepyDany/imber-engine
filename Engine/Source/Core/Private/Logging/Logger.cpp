// Copyright ImberEngine. All rights reserved.
#include "Public/Logging/Logger.h"

#include "Public/Logging/Sinks/LogSink.h"

#include <cassert>

namespace Imber::Logging
{
	LoggerBase::LoggerBase(const std::string& name,
		ELogVerbosity::Type defaultVerbosity,
		ELogVerbosity::Type maxVerbosity,
		const std::vector<std::shared_ptr<ILogSink>>& sinks)
		: Name(name), CurrentVerbosity(defaultVerbosity), DefaultVerbosity(defaultVerbosity), MaxVerbosity(maxVerbosity)
	{
		Sinks.reserve(sinks.size());
		SinkNames.reserve(sinks.size());
		for (auto& sink : sinks)
		{
			if (sink)
			{
				Sinks.push_back(sink);
				SinkNames.push_back(sink->GetName());
			}
		}
	}

	LoggerBase::~LoggerBase()
	{
		Sinks.clear();
	}

	void LoggerBase::SetCurrentVerbosity(ELogVerbosity::Type newVerbosity)
	{
		assert((newVerbosity & ELogVerbosity::VerbosityMask) <= MaxVerbosity /*, "Invalid verbosity specified"*/);
	}

	inline std::vector<std::string> LoggerBase::GetSinkNames() const
	{
		return SinkNames;
	}

	void LoggerBase::ResetToDefaultVerbosity()
	{
		CurrentVerbosity = DefaultVerbosity;
	}

} // namespace Imber::Logging