// Copyright ImberEngine. All rights reserved.
#pragma once

#include "Core/Public/Types/BaseTypes.h"
#include "CoreDefinitions.h"

#include <chrono>
#include <vector>

namespace Imber::ELogVerbosity
{
	enum Type : uint8
	{
		NoLogging = 0,

		/** Always prints fatal error to every sink and crashes, even if logging is disabled
		 *
		 * TODO: Red
		 **/
		Fatal,

		/** Prints error to every sink
		 *
		 * TODO: Should collect and report errors
		 * TODO: Red
		 **/
		Error,

		/** Prints warnigns to every sink
		 *
		 * TODO: Should collect and report warnings
		 * TODO: Should add possibility to treat warnings as errors
		 * TODO: Yellow
		 **/
		Warning,

		/** Prints message to every sink
		 *
		 * TODO: White
		 **/
		Debug,

		/** Prints message to every sink
		 *
		 * TODO: White
		 **/
		Info,

		/** Prints message to every sink (usually used for detailed logging)
		 *
		 * TODO: White
		 **/
		Verbose,

		All = Verbose,
		VerbosityNum = Verbose + 1,
		VerbosityMask = 0xF
	};

	/** Converts verbosity to string
	 *
	 * TODO: API _declspec
	 **/
	DLLEXPORT constexpr std::string ToString(ELogVerbosity::Type verbosity);

	/** Converts string to verbostiy
	 *
	 * TODO: API _declspec
	 **/
	DLLEXPORT constexpr ELogVerbosity::Type FromString(const std::string& verbosityString);

} // namespace Imber::ELogVerbosity

static_assert(Imber::ELogVerbosity::VerbosityNum - 1 < Imber::ELogVerbosity::VerbosityMask, "Bad verbosity mask");

namespace Imber::Logging
{
	struct LogContext
	{
		std::string LoggerName;
		std::string Message;
		std::string File;
		std::string Function;
		int32 Line;
		Imber::ELogVerbosity::Type LoggerVerbosity;
		std::chrono::system_clock::time_point Timestamp;

		std::vector<std::string> SinkNames;
	};

} // namespace Imber::Logging