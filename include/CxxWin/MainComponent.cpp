/***************************************************************************//**
 * @file MainComponent.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief Contains the definitions of 'MainComponent'.
 * @version 1.0.0
 * @date 2023-08-28
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

// #include "modules/Win32_core/win32_core.mm"

#include "MainComponent.hpp"

/**
 * @brief Construct a new 'MainComponent' object.
 *
 */
MainComponent::MainComponent()
  : pFactory (NULL)
  , pRenderTarget (NULL)
  , pBrush (NULL)
  , pBrushB (NULL)
  , pBrushC (NULL)
  , ellipseA (D2D1::Ellipse(D2D1::Point2F(), 0.0F, 0.0F))
  , ellipseB (D2D1::Ellipse(D2D1::Point2F(), 0.0F, 0.0F))
  , ellipseC (D2D1::Ellipse(D2D1::Point2F(), 0.0F, 0.0F))
  , ptMouse (D2D1::Point2F())
{

}

/**
 * @brief
 *
 * @return PCWSTR
 */
PCWSTR MainComponent::ClassName() const
{
    return CXXWIN_LONG_NAME;
}

/**
 * @brief A typical window procedure is simply a large 'switch()' statement that
 * switches on the 'uMsg' code. Add cases for each message that you want to
 * handle.
 *
 * @param uMsg
 * @param wParam
 * @param lParam
 * @return LRESULT
 */
LRESULT MainComponent::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:

        if (FAILED(OnCreate()))
        {
            return -1;
        }
        DPIScale::Initialize(pFactory);
        return 0;

    case WM_CLOSE:

        OnClose();
        return 0;

    case WM_DESTROY:

        OnDestroy();
        return 0;

    case WM_SIZE:
        /**
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);

            OnSize(m_hwnd, (UINT)wParam, width, height);
        }
        */
        Resize();
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    default:

        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }

    return TRUE;
}

/**
 * @brief
 *
 */
void MainComponent::Resize()
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

/**
 * @brief
 *
 */
void MainComponent::CalculateLayout()
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
 */
void MainComponent::OnPaint()
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

        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(m_hwnd, &ps);
    }
}

/**
 * @brief
 *
 * @return HRESULT
 */
HRESULT MainComponent::CreateGraphicsResources()
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
void MainComponent::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
    SafeRelease(&pBrushB);
    SafeRelease(&pBrushC);
}

/**
 * @brief
 *
 * @return HRESULT
 */
HRESULT MainComponent::OnCreate()
{
    return (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory));
}

/**
 * @brief
 *
 */
void MainComponent::OnClose() CONST
{
    if (MessageBox(m_hwnd, TEXT("Sure?"), ClassName(), MB_OKCANCEL) == IDOK)
    {
        DestroyWindow(m_hwnd);
    }
}

/**
 * @brief
 *
 */
void MainComponent::OnDestroy()
{
    DiscardGraphicsResources();
    SafeRelease(&pFactory);
    PostQuitMessage(0);
}
