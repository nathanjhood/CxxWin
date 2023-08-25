/**
 * @file win32_DPIScale.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#ifndef WINVER
#  define WINVER 0x0A00
#endif

#ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x0A00
#endif

#ifdef D2D_USE_C_DEFINITIONS
#  undef D2D_USE_C_DEFINITIONS
#endif

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class DPIScale
{
public:
    static void Initialize(HWND hwnd);

    template <typename T>
    static D2D1_POINT_2F PixelsToDips(T x, T y);
private:
    static float scale;
};
