/***************************************************************************//**
 * @file win32_StandardHeader.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Contains some standard definitions, functions, and includes familiar
 * to all supported platforms and architectures.
 *
 * @version 1.0.0
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once
/**
 * @brief Contains some standard definitions, functions, and includes familiar
 * to all supported platforms and architectures.
 *
 */
#define _WIN32_STANDARDHEADER_HPP_

/**
 * If the compiler does not have __has_*(), pretend the answer is always no.
 */
#ifndef	__has_attribute
#define	__has_attribute(x)	0
#endif
#ifndef	__has_extension
#define	__has_extension		__has_feature
#endif
#ifndef	__has_feature
#define	__has_feature(x)	0
#endif
#ifndef	__has_include
#define	__has_include(x)	0
#endif
#ifndef	__has_builtin
#define	__has_builtin(x)	0
#endif

#ifndef STRINGIFY_HELPER
/** Helper macro to quote an argument, turning it into a string. */
#  define STRINGIFY_HELPER(X) #X
#endif

#ifndef STRINGIFY
/** Quote the argument, turning it into a string. */
#  define STRINGIFY(X) STRINGIFY_HELPER(X)
#endif

#ifndef CONCAT_HELPER
/** Helper macro to concatenate two tokens to form a new token. */
#  define CONCAT_HELPER(a, b) a##b
#endif

#ifndef CONCAT
/** Concatenate two tokens to form a new token. */
#  define CONCAT(a, b) CONCAT_HELPER(a, b)
#endif

/**
 * @name DEC
 * @brief Convert integer to decimal digit literals.
 */
#if !defined(DEC)
#	 define  DEC(n)					  \
	   ('0' + (((n) / 10000000)%10)), \
	   ('0' + (((n) / 1000000)%10)),  \
	   ('0' + (((n) / 100000)%10)),   \
	   ('0' + (((n) / 10000)%10)),    \
	   ('0' + (((n) / 1000)%10)),     \
	   ('0' + (((n) / 100)%10)),      \
	   ('0' + (((n) / 10)%10)),       \
	   ('0' +  ((n) % 10))
#endif

/**
 * @name HEX
 * @brief Convert integer to hex digit literals.
 */
#if !defined(HEX)
#	 define  HEX(n)				 \
	    ('0' + ((n)>>28 & 0xF)), \
	    ('0' + ((n)>>24 & 0xF)), \
	    ('0' + ((n)>>20 & 0xF)), \
	    ('0' + ((n)>>16 & 0xF)), \
	    ('0' + ((n)>>12 & 0xF)), \
	    ('0' + ((n)>>8  & 0xF)), \
		('0' + ((n)>>4  & 0xF)), \
	 	('0' + ((n)     & 0xF))
#endif

//==============================================================================
/** Current version number (major). */
#define CXXWIN_VERSION_MAJOR      1
/** Current version number (minor). */
#define CXXWIN_VERSION_MINOR      0
/** Current version number (patch). */
#define CXXWIN_VERSION_PATCH      1

/** Current version number.

    Bits 16 to 32 = major version.
    Bits 8 to 16 = minor version.
    Bits 0 to 8 = point release.
*/
#define CXXWIN_VERSION   ((CXXWIN_VERSION_MAJOR << 16) + (CXXWIN_VERSION_MINOR << 8) + CXXWIN_VERSION_PATCH)

#if ! DOXYGEN
#define CXXWIN_VERSION_ID \
    [[maybe_unused]] volatile auto CxxWinVersionId = "cxxwin_version_" STRINGIFY(CXXWIN_VERSION_MAJOR) "_" STRINGIFY(CXXWIN_VERSION_MINOR) "_" STRINGIFY(CXXWIN_VERSION_PATCH);
#endif

#define CXXWIN_LONG_NAME TEXT("CxxWin") STRINGIFY(.) STRINGIFY(CXXWIN_VERSION_MAJOR) STRINGIFY(.) STRINGIFY(CXXWIN_VERSION_MINOR) STRINGIFY(.) STRINGIFY(CXXWIN_VERSION_PATCH)

// const wchar_t* str = { CXXWIN_LONG_NAME };

//==============================================================================

#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <thread>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

//==============================================================================

#include "win32_CompilerSupport.hpp"
#include "win32_PlatformDefs.hpp"

//==============================================================================
// Now we'll include some common OS headers..
// JUCE_BEGIN_IGNORE_WARNINGS_MSVC (4514 4245 4100)

#if MSVC
#  include <intrin.h>
#endif


#if defined(__PLATFORM_IS_MAC) || defined(__PLATFORM_IS_IOS)
#  include <libkern/OSAtomic.h>
#  include <xlocale.h>
#  include <signal.h>
#endif

#if defined(__PLATFORM_IS_LINUX) || defined(__PLATFORM_IS_BSD)
#  include <cstring>
#  include <signal.h>

#  if __INTEL_COMPILER
#    if __ia64__
#      include <ia64intrin.h>
#    else
#      include <ia32intrin.h>
#    endif
#  endif
#endif

#if MSVC && _DEBUG
#  include <crtdbg.h>
#endif

// JUCE_END_IGNORE_WARNINGS_MSVC

#ifdef __PLATFORM_IS_MINGW
#  include <cstring>
#  include <sys/types.h>
#endif

#ifdef __PLATFORM_IS_ANDROID
#  include <cstring>
#  include <byteswap.h>
#endif

// undef symbols that are sometimes set by 3rd-party headers..
// #undef TYPE_BOOL
#undef max
#undef min
#undef major
#undef minor
#undef KeyPress
