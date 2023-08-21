/**
 * @file CxxWin/entry.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _CXX_WIN_ENTRY_H_
#define _CXX_WIN_ENTRY_H_

/* 'UNICODE' for 16-bit chars instead of ANSI-style 8-bit ('double-wide') */
#ifndef   UNICODE
#  define UNICODE
#endif
#ifndef   _UNICODE
#  define _UNICODE
#endif

#include <windows.h>

#include "CxxWin/MainWindow.h"

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);

#endif /* _CXX_WIN_ENTRY_H_ */
