/**
 * @file win32_DPIScale.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "win32_DPIScale.h"

float DPIScale::scale = 1.0F;

void DPIScale::Initialize(HWND hwnd)
{
    const float oDpi = 96.0F;
    float dpi = static_cast<float>(GetDpiForWindow(hwnd));
    scale = dpi / oDpi;
}

template <typename T>
D2D1_POINT_2F DPIScale::PixelsToDips(T x, T y)
{
    return D2D1::Point2F(static_cast<float>(x) / scale, static_cast<float>(y) / scale);
}
