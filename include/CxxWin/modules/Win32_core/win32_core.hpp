/***************************************************************************//**
 * @file win32_core.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief
 *
 * @version 1.0.0-init
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once

#define _WIN32_CORE_H_

#include "system/win32_TargetPlatform.hpp"

#include "native/win32_BasicNativeHeaders.hpp"

#ifdef __PLATFORM_IS_WINDOWS
#  undef small
#endif

#include "system/win32_StandardHeader.hpp"
#include "native/win32_Unicode.hpp"

#include "memory/win32_SmartPointer.hpp"

#include "window/win32_DPIScale.hpp"
#include "window/win32_BaseWindow.hpp"
#include "window/win32_MainWindow.hpp"

/** @brief The 'DPIScale' datatype. */
#define _DPIScale_T DPIScale
/** @brief The 'DPIScale' datatype. */
typedef class _DPIScale_T DPIScale;

/** @brief The 'DPIScale' datatype. */
#define _MainWindow_T MainWindow
/** @brief The 'MainWindow' datatype. */
typedef class _MainWindow_T MainWindow;
