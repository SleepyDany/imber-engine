// Copyright ImberEngine. All rights reserved.
#pragma once

// disabled by default: 'identifier': unmanaged formal parameter
#pragma warning(disable : 4100)
// disabled by default: 'function': removed built-in function without references
#pragma warning(disable : 4514)
// disabled by default: 'derived class': Could not create copy constructor because the copy constructor for the base class is not accessible
// or has been deleted
#pragma warning(disable : 4625)
// disabled by default: 'derived class': assignment operator could not be created because the assignment operator for the base class is not
// available or has been deleted
#pragma warning(disable : 4626)
// disabled by default: "bytes" padding bytes added after creation of "member_name"
#pragma warning(disable : 4820)
// disabled by default: 'type': move constructor was implicitly defined as deleted
#pragma warning(disable : 5026)
// disabled by default: 'type': move assignment operator was implicitly defined as remote
#pragma warning(disable : 5027)
// disabled by default: The compiler inserts Spectre mitigations for memory loading if the /Qspectre option is specified.
#pragma warning(disable : 5045)

#if defined(_WIN32)
	#define IMBER_WIN32 1
#elif defined(_WIN64)
	#define IMBER_WIN64 1
#elif defined(__linux)
	#define IMBER_LINUX 1
#endif

// DLL export and import definitions
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
