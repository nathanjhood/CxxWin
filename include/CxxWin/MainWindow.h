/**
 * @file Cxxwin/MainWindow.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _CXX_WIN_MAIN_WINDOW_H_
#define _CXX_WIN_MAIN_WINDOW_H_

/** 'UNICODE' for 16-bit chars instead of ANSI-style 8-bit ('double-wide') */
#ifndef   UNICODE
#  define UNICODE
#endif
#ifndef   _UNICODE
#  define _UNICODE
#endif

#include <windows.h>

#include "CxxWin/BaseWindow.h"

void OnSize(HWND hwnd, UINT flag, int width, int height);

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR ClassName() const;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif /** _CXX_WIN_MAIN_WINDOW_H_ */
