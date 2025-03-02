// Copyright ImberEngine. All rights reserved.
#pragma once

#include "Core/Public/Logging/Logger.h"

#define DECLARE_IMBER_LOG(LoggerName, DefaultVerbosity, MaxVerbosity) \
	Imber::Logger<DefaultVerbosity, MaxVerbosity> LoggerName##Logger(#LoggerName, DefaultVerbosity, MaxVerbosity);

#define IMBER_PRIVATE_LOG(LoggerName, IfExpression, Verbosity, File, Function, Line, Format, ...)               \
	static_assert(Verbosity > 0, "Invalid Verbosity: should be equal or greater than 0");                       \
	static_assert(Verbosity < ELogVerbosity::MAX, "Invalid Verbosity: should be less than ELogVerbosity::MAX"); \
	if IfExpression (LoggerName##Logger.GetMaxVerbosity() >= Verbosity)                                         \
	{                                                                                                           \
		/* TODO: Check for compile time format string */                                                        \
		LoggerName##Logger.Log(Verbosity, File, Function, Line, Format, __VA_ARGS__);                           \
	}

#define IMBER_LOG(LoggerName, Verbosity, Format, ...) \
	IMBER_PRIVATE_LOG(LoggerName, , Verbosity, __FILE__, __FUNCTION__, __LINE__, Format, __VA_ARGS__);
