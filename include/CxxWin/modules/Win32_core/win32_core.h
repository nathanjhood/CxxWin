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
#pragma once

#define _WIN32_CORE_H_

#include "system/win32_TargetPlatform.h"

#include "native/win32_BasicNativeHeaders.h"

#ifdef __PLATFORM_IS_WINDOWS
#  undef small
#endif

#include "system/win32_StandardHeader.h"
#include "native/win32_Unicode.h"

#include "memory/win32_SmartPointer.h"

#include "window/win32_DPIScale.h"
#include "window/win32_BaseWindow.h"
#include "window/win32_MainWindow.h"

/**
 * @brief The 'DPIScale' datatype.
 * typedef class DPIScale DPIScale;
 */


/**
 * @brief The 'MainWindow' datatype.
 * typedef class MainWindow MainWindow;
 */
