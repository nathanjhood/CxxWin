/***************************************************************************//**
 * @file MainComponent.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief Contains the declarations of 'MainComponent'.
 * @version 1.0.0-init
 * @date 2023-08-28
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#pragma once
/** Contains the declarations of 'MainComponent'. */
#define __MAIN_COMPONENT_H

// #ifdef __cplusplus
// extern "C" {
// #endif

// #if defined(window_WIN32_SHARED)
// #if defined(window_WIN32_EXPORTS)
// #   define window_EXPORT __declspec(dllexport)
// #else
// #   define window_EXPORT __declspec(dllimport)
// #endif
// #else
// #   define window_EXPORT
// #endif

// #ifdef __cplusplus
// }
// #endif

#include "modules/Win32_core/win32_core.h"

/**
 * @brief The 'MainComponent' class.
 *
 */
class MainComponent                   : public MainWindow
{
public:
    MainComponent();

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

    // IFileOpenDialog*                     pFileOpen;
    // SmartPointer<IFileOpenDialog>        pFileOpen;

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
