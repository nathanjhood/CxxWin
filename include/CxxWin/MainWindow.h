/**
 * @file Cxxwin/MainWindow.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _CXX_WIN_MAIN_WINDOW_H_
#define _CXX_WIN_MAIN_WINDOW_H_

#include "BaseWindow.h"

void OnSize(HWND hwnd, UINT flag, int width, int height);

class MainWindow : public BaseWindow<MainWindow>
{
public:
    PCWSTR ClassName() const;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif /** _CXX_WIN_MAIN_WINDOW_H_ */
