// Copyright ImberEngine. All rights reserved.
#include "Core/Public/Logging/LogVerbosity.h"

namespace Imber::ELogVerbosity
{
	constexpr std::string ToString(ELogVerbosity::Type verbosity)
	{
		switch (verbosity)
		{
		case ELogVerbosity::NoLogging:
		{
			return "NoLogging";
		}
		case ELogVerbosity::Fatal:
		{
			return "Fatal";
		}
		case ELogVerbosity::Error:
		{
			return "Error";
		}
		case ELogVerbosity::Warning:
		{
			return "Warning";
		}
		case ELogVerbosity::Debug:
		{
			return "Debug";
		}
		case ELogVerbosity::Info:
		{
			return "Info";
		}
		case ELogVerbosity::Verbose:
		{
			return "Verbose";
		}
		case VerbosityNum:
		case VerbosityMask:
		default:
		{
			return "Unknown verbosity";
		}
		}
	}

	constexpr ELogVerbosity::Type FromString(const std::string& verbosityString)
	{
		if (verbosityString == "NoLogging")
		{
			return ELogVerbosity::NoLogging;
		}
		else if (verbosityString == "Fatal")
		{
			return ELogVerbosity::Fatal;
		}
		else if (verbosityString == "Error")
		{
			return ELogVerbosity::Error;
		}
		else if (verbosityString == "Warning")
		{
			return ELogVerbosity::Warning;
		}
		else if (verbosityString == "Debug")
		{
			return ELogVerbosity::Debug;
		}
		else if (verbosityString == "Info")
		{
			return ELogVerbosity::Info;
		}
		else if (verbosityString == "Verbose" || verbosityString == "All")
		{
			return ELogVerbosity::Verbose;
		}

		// by default invalid verbosity string converts to NoLogging
		return ELogVerbosity::NoLogging;
	}

} // namespace Imber::ELogVerbosity