/**
 * @file Mouse.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _CXX_WIN_MOUSE_H_
#define _CXX_WIN_MOUSE_H_

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
#include <windowsX.h>

class Mouse
{
public:
    Mouse();
    Mouse(bool enableTracking);
    ~Mouse();
    void OnMouseMove(HWND hwnd);
    void Reset(HWND hwnd);
    UINT GetMouseHoverTime();
private:
    bool _b_MouseTracking;
};

#endif /** _CXX_WIN_MOUSE_H_ */
