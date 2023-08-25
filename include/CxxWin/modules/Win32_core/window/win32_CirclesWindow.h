/**
 * @file win32_CirclesWindow.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _CXX_WIN_CIRCLE_H_
#define _CXX_WIN_CIRCLE_H_

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
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <string>
#include <iostream>

#include "win32_DPIScale.h"
#include "win32_BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{
public:
    MainWindow();
    ~MainWindow();

    PCWSTR ClassName () CONST;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
    void CalculateLayout();
    HRESULT CreateGraphicsResources();
    void DiscardGraphicsResources();
    HRESULT OnCreate();
    void OnPaint();
    void Resize();
    void OnClose() CONST;
    void OnDestroy();

    void OnLButtonDown(int pixelX, int pixelY, DWORD flags);
    void OnLButtonUp();
    void OnMouseMove(int pixelX, int pixelY, DWORD flags);

    ID2D1Factory*           pFactory;
    ID2D1HwndRenderTarget*  pRenderTarget;
    ID2D1SolidColorBrush*   pBrush;
    ID2D1SolidColorBrush*   pBrushB;
    ID2D1SolidColorBrush*   pBrushC;
    D2D1_ELLIPSE            ellipseA;
    D2D1_ELLIPSE            ellipseB;
    D2D1_ELLIPSE            ellipseC;

    D2D1_ELLIPSE            ellipseMouse;

    D2D1_POINT_2F           ptMouseDown;
};

#endif /* _CXX_WIN_CIRCLE_H_ */
