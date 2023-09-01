/***************************************************************************//**
 * @file win32_core.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#ifdef _WIN32_CORE_H_
#  error "Incorrect useage of 'win32_core.cpp' file!"
#endif

#include "win32_core.hpp"

#include <cctype>
#include <cstdarg>
#include <locale>
#include <thread>

#if !defined(__PLATFORM_IS_ANDROID) || !defined(__PLATFORM_IS_BSD)
#  include <sys/timeb.h>
#  include <cwctype>
#endif

#if defined(__PLATFORM_IS_WINDOWS)
#  include <ctime>

#  if defined(__PLATFORM_IS_MINGW)
#    include <ws2spi.h>
#    include <cstdio>
#    include <locale.h>
#  else
// JUCE_BEGIN_IGNORE_WARNINGS_MSVC (4091)
#    include <Dbghelp.h>
// JUCE_END_IGNORE_WARNINGS_MSVC

#    if !defined(__DONT_AUTOLINK_TO_WIN32_LIBRARIES)
#      pragma comment (lib, "DbgHelp.lib")
#    endif
#  endif

#else
#  if defined(__PLATFORM_IS_LINUX) || defined(__PLATFORM_IS_BSD) || defined(__PLATFORM_IS_ANDROID)
#    include <sys/types.h>
#    include <sys/socket.h>
#    include <sys/errno.h>
#    include <unistd.h>
#    include <netinet/in.h>
#  endif

 #if defined(__PLATFORM_IS_WASM)
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <errno.h>
  #include <unistd.h>
  #include <netinet/in.h>
  #include <sys/stat.h>
 #endif

 #if defined(__PLATFORM_IS_LINUX) || (__PLATFORM_IS_BSD)
  #include <stdio.h>
  #include <langinfo.h>
  #include <ifaddrs.h>
  #include <sys/resource.h>

  #if USE_CURL
   #include <curl/curl.h>
  #endif
 #endif

 #include <pwd.h>
 #include <fcntl.h>
 #include <netdb.h>
 #include <arpa/inet.h>
 #include <netinet/tcp.h>
 #include <sys/time.h>
 #include <net/if.h>
 #include <sys/ioctl.h>

 #if !defined(__PLATFORM_IS_ANDROID) || !defined(__PLATFORM_IS_WASM)
  #include <execinfo.h>
 #endif
#endif

#if defined(__PLATFORM_IS_MAC) || defined(__PLATFORM_IS_IOS)
 #include <xlocale.h>
 #include <mach/mach.h>
#endif

#if defined(__PLATFORM_IS_ANDROID)
 #include <ifaddrs.h>
 #include <android/log.h>
#endif

#undef check

//==============================================================================

// include lib .cpp files here
