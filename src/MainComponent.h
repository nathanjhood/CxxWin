#pragma once
/***************************************************************************//**
 * @file MainComponent.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-28
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#define MAIN_COMPONENT_H

#include "CxxWin/modules/Win32_core/win32_core.h"

/**
 * @brief The 'MainComponent' class.
 *
 */
class MainComponent                   : public MainWindow
{
public:
    MainComponent();
    ~MainComponent();

    PCWSTR ClassName() CONST;
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    void CalculateLayout();
    HRESULT CreateGraphicsResources();
    void DiscardGraphicsResources();

    HRESULT OnCreate();
    void OnPaint();
    void Resize();
    void OnClose() CONST;
    void OnDestroy();

private:

    /**
     * @brief Pointer to an 'ID2D1Factory' struct.
     *
     * @headerfile d2d1.h
     *
     */
    ID2D1Factory*                       pFactory;
    ID2D1HwndRenderTarget*              pRenderTarget;
    ID2D1SolidColorBrush*               pBrush;
    ID2D1SolidColorBrush*               pBrushB;
    ID2D1SolidColorBrush*               pBrushC;
    D2D1_ELLIPSE                        ellipseA;
    D2D1_ELLIPSE                        ellipseB;
    D2D1_ELLIPSE                        ellipseC;

    D2D1_POINT_2F                       ptMouse;
};
