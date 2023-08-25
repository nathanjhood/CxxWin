/***************************************************************************//**
 * @file TargetPlatform.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#pragma once

#ifdef _WIN32_APP_CONFIG_H_
#include _WIN32_APP_CONFIG_H_
#endif

/**
 * Compiler support
 *
 */
#if defined (__clang__)
#elif defined (__GNUC__)
#elif defined (_MSC_VER)
#else
#  error "Compiler unknown?"
#endif

#if defined(_MSVC_LANG) || defined(__cplusplus)
#  define CXX_WIN_COMPILER_IS_CXX 1
#else
#  define CXX_WIN_COMPILER_IS_CXX 0
#endif

#if CXX_WIN_COMPILER_IS_CXX
#  define CXX_WIN_BEGIN_DECLS  extern "C" {
#  define CXX_WIN_END_DECLS    }
#else
#  define CXX_WIN_BEGIN_DECLS
#  define CXX_WIN_END_DECLS
#endif
