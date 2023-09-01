/***************************************************************************//**
 * @file win32_TargetPlatform.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Provides some preprocessor feature detection handlers to attempt to
 * ascertain information about the build architecture and platform.
 *
 * @version 1.0.0
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once
/**
 * @brief Provides some preprocessor feature detection handlers to attempt to
 * ascertain information about the build architecture and platform.
 *
 */
#define _WIN32_TARGETPLATFORM_HPP_

#if defined(__x86_64) && \
  !(defined(_X86_) || defined(__i386__) || defined(_IA64_))
#if !defined(_AMD64_)
#define __ARCHITECTURE_IS_AMD64 // _AMD64_
#endif
#endif

#if defined(__ia64__) && \
  !(defined(_X86_) || defined(__x86_64) || defined(_AMD64_))
#if !defined(_IA64_)
#define __ARCHITECTURE_IS_IA64_ // _IA64_
#endif
#endif

#if defined(__ia64__) || defined(__x86_64)
#define __ARCHITECTURE_IS_X64  //__WIN64__
#else
#if !defined (_ARM_)
#define __ARCHITECTURE_IS_X86 // __WIN32__
#else
#define __ARCHITECTURE_IS_ARM32 // __ARM32__
#endif
#endif


/**
 * Platform check macros
 *
 */

#if defined(__MSYS__) || defined(MSYS)
#  define __PLATFORM_IS_MSYS 1
#endif

#if defined(__CYGWIN__) || defined (CYGWIN)
#  define __PLATFORM_IS_CYGWIN 1
#endif

#if defined (__MINGW64__) || defined(__MINGW32__) || defined (MINGW)
#  define __PLATFORM_IS_MINGW 1
#endif

#if defined(_WIN32) || defined(__WIN32__) || defined (WIN32)
#  define __PLATFORM_IS_WINDOWS 1
#endif

#if  defined (__linux__) || defined (__linux) || defined (linux)
#  define __PLATFORM_IS_LINUX 1
#endif

#if defined (__APPLE__)
#  define __PLATFORM_IS_DARWIN 1
#endif

#if defined (__FreeBSD__) || defined (__FreeBSD)
#  define __PLATFORM_IS_FREEBSD 1
#endif

#if defined (__NetBSD__) || defined (__NetBSD)
#  define __PLATFORM_IS_NETBSD 1
#endif

#if defined (__OpenBSD__) || defined (__OPENBSD)
#  define __PLATFORM_IS_OPENBSD 1
#endif

#if  defined (__unix__) || defined (__unix) || defined (unix)
#  define __PLATFORM_IS_UNIX 1
#endif

#ifndef _XOPEN_UNIX
#  if (__PLATFORM_IS_UNIX) && defined (_XOPEN_SOURCE)
#    define _XOPEN_UNIX 1
#  endif
#endif

#ifdef _XOPEN_VERSION
#  if (_XOPEN_VERSION >= 3)
#    define __STANDARD_XOPEN_1989 1
#  endif
#  if (_XOPEN_VERSION >= 4)
#    define __STANDARD_XOPEN_1992 1
#  endif
#  if (_XOPEN_VERSION >= 4) && defined(_XOPEN_UNIX)
#    define __STANDARD_XOPEN_1995
#  endif
#  if (_XOPEN_VERSION >= 500)
#    define __STANDARD_XOPEN_1998 1
#  endif
#  if (_XOPEN_VERSION >= 600)
#    define __STANDARD_XOPEN_2003 1
#  endif
#  if (_XOPEN_VERSION >= 700)
#    define __STANDARD_XOPEN_2008 1
#  endif
#endif
