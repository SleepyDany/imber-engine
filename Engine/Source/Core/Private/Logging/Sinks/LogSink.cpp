#include "Public/Logging/Sinks/LogSink.h"

namespace Imber::Logging
{
	ILogSink::ILogSink(const std::string& name) : Name(name)
	{
	}

} // namespace Imber::Logging