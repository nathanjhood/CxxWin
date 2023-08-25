/**
 * @file win32_CirclesWindow.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../memory/win32_SmartPointer.h"
#include "win32_CirclesWindow.h"

/** float DPIScale::scale = 1.0F; */

/**
 * @brief Construct a new Main Window:: Main Window object
 *
 */
MainWindow::MainWindow() :
    pFactory(NULL),
    pRenderTarget(NULL),
    pBrush(NULL),
    pBrushB(NULL),
    pBrushC(NULL),
    ellipseA(D2D1::Ellipse(D2D1::Point2F(), 0.0F, 0.0F)),
    ellipseB(D2D1::Ellipse(D2D1::Point2F(), 0.0F, 0.0F)),
    ellipseC(D2D1::Ellipse(D2D1::Point2F(), 0.0F, 0.0F)),
    ellipseMouse(D2D1::Ellipse(D2D1::Point2F(), 0.0F, 0.0F)),
    ptMouseDown(D2D1::Point2F())
{

}

MainWindow::~MainWindow()
{
    if (pBrush != NULL) {
        pBrush->Release();
    }
    if (pBrushB != NULL) {
        pBrushB->Release();
    }
    if (pBrushC != NULL) {
        pBrushC->Release();
    }
    if (pFactory != NULL) {
        pFactory->Release();
    }
    if (pRenderTarget != NULL) {
        pRenderTarget->Release();
    }
}

/**
 * @brief
 *
 * @return PCWSTR
 */
PCWSTR MainWindow::ClassName () const
{
    return L"Circle Window Class";
}

/**
 * @brief
 *
 */
void MainWindow::CalculateLayout()
{
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize();

        const float x = size.width / 2.0F;
        const float y = size.height / 2.0F;
        const float radius = (((x) < (y)) ? (x) : (y));

        ellipseA = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);

        const float halfX = x / 2.0F;
        const float halfY = y / 2.0F;
        const float halfPi = radius / 2.0F;

        ellipseB = D2D1::Ellipse(D2D1::Point2F(halfX, halfY), halfPi, halfPi);

        const float quartX = halfX / 2.0F;
        const float quartY = halfY / 2.0F;
        const float quartPi = halfPi / 2.0F;

        ellipseC = D2D1::Ellipse(D2D1::Point2F(quartX, quartY), quartPi, quartPi);
    }
}

/**
 * @brief
 *
 * @return HRESULT
 */
HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;

    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &pRenderTarget
        );

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0F, 1.0F, 0.0F, 0.5F);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

            if (SUCCEEDED(hr))
            {
                const D2D1_COLOR_F colorB = D2D1::ColorF(1.0F, 0.0F, 0.0F, 0.5F);
                hr = pRenderTarget->CreateSolidColorBrush(colorB, &pBrushB);

                if (SUCCEEDED(hr))
                {
                    const D2D1_COLOR_F colorC = D2D1::ColorF(0.0F, 0.0F, 1.0F, 0.5F);
                    hr = pRenderTarget->CreateSolidColorBrush(colorC, &pBrushC);

                    if (SUCCEEDED(hr))
                    {
                        CalculateLayout();
                    }
                }
            }
        }
    }
    return hr;
}

/**
 * @brief
 *
 */
void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
    SafeRelease(&pBrushB);
    SafeRelease(&pBrushC);
}

/**
 * @brief
 *
 */
void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::CadetBlue));
        pRenderTarget->FillEllipse(ellipseA, pBrush);
        pRenderTarget->FillEllipse(ellipseB, pBrushB);
        pRenderTarget->FillEllipse(ellipseC, pBrushC);

        pRenderTarget->FillEllipse(ellipseMouse, pBrushC);

        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(m_hwnd, &ps);
    }
}

HRESULT MainWindow::OnCreate()
{
    return (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory));
}

/**
 * @brief
 *
 */
void MainWindow::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        CalculateLayout();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

void MainWindow::OnClose() CONST
{
    if (MessageBox(m_hwnd, L"Sure?", L"CxxWin", MB_OKCANCEL) == IDOK)
    {
        DestroyWindow(m_hwnd);
    }
}

void MainWindow::OnDestroy()
{
    DiscardGraphicsResources();
    SafeRelease(&pFactory);
    PostQuitMessage(0);
}

void MainWindow::OnLButtonDown(int pixelX, int pixelY, DWORD flags)
{
    SetCapture(m_hwnd);
    ellipseMouse.point = ptMouseDown = DPIScale::PixelsToDips(pixelX, pixelY);
    ellipseMouse.radiusX = ellipseMouse.radiusY = 1.0F;
    InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnLButtonUp()
{
    ReleaseCapture();
}

void MainWindow::OnMouseMove(int pixelX, int pixelY, DWORD flags)
{
    if (flags & MK_LBUTTON)
    {
        const D2D1_POINT_2F dips = DPIScale::PixelsToDips(pixelX, pixelY);

        const float width = (dips.x - ptMouseDown.x) / 2.0F;
        const float height = (dips.y - ptMouseDown.y) / 2.0F;

        const float x1 = ptMouseDown.x + width;
        const float y1 = ptMouseDown.y + height;

        ellipseMouse = D2D1::Ellipse(D2D1::Point2F(x1, y1), width, height);

        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_CREATE:

        if (FAILED(OnCreate()))
        {
            return -1;
        }
        DPIScale::Initialize(m_hwnd);
        return 0;

    case WM_LBUTTONDOWN:
        OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;

    case WM_LBUTTONUP:
        OnLButtonUp();
        return 0;

    case WM_MOUSEMOVE:
        OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
        return 0;

    case WM_PAINT:

        OnPaint();
        return 0;

    case WM_SIZE:

        Resize();
        return 0;

    case WM_CLOSE:

        OnClose();
        return 0;

    case WM_DESTROY:

        OnDestroy();
        return 0;
    }

    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}
