#pragma once
/***************************************************************************//**
 * @file win32_core.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#define _WIN32_CORE_H_

#ifndef WINVER
#  define WINVER 0x0A00 // _WIN32_WINNT_WINTHRESHOLD
#endif

#ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x0A00 // _WIN32_WINNT_WINTHRESHOLD
#endif

#ifdef D2D_USE_C_DEFINITIONS
#  undef D2D_USE_C_DEFINITIONS
#endif

#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "memory/win32_SmartPointer.h"

#include "system/win32_TargetPlatform.h"

#include "window/win32_DPIScale.h"

#include "window/win32_BaseWindow.h"
#include "window/win32_MainWindow.h"

/**
 * @brief The 'DPIScale' datatype.
 *
 */
typedef class DPIScale DPIScale;

/**
 * @brief The 'MainWindow' datatype.
 *
 */
typedef class MainWindow MainWindow;
