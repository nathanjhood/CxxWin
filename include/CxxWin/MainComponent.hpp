/***************************************************************************//**
 * @file MainComponent.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief Contains the declarations of 'MainComponent'.
 * @version 1.0.0
 * @date 2023-08-28
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#pragma once
/** Contains the declarations of 'MainComponent'. */
#define _MAIN_COMPONENT_HPP_

#include "modules/Win32_core/win32_core.hpp"
// #include "modules/Win32_resource/win32_resource.hpp"

// namespace Win32
// {
/**
 * @brief The 'MainComponent' class.
 *
 */
class MainComponent              : public MainWindow
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

// } // namespace Win32
