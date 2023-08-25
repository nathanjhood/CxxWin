/**
 * @file CxxWin/MainWindow.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "win32_MainWindow.h"

/**
 * @brief
 *
 * @param hwnd
 * @param flag
 * @param width
 * @param height
 */
void OnSize(HWND hwnd, UINT flag, int width, int height)
{

}

/**
 * @brief
 *
 * @return PCWSTR
 */
PCWSTR MainWindow::ClassName() const
{
    return L"Sample Window Class";
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
LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:

        if (MessageBox(m_hwnd, L"Sure?", L"CxxWin", MB_OKCANCEL) == IDOK)
        {
            DestroyWindow(m_hwnd);
        }
        return 0;

    case WM_DESTROY:
        {
            PostQuitMessage(0);
        }
        return 0;

    case WM_SIZE:
        {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);

            OnSize(m_hwnd, (UINT)wParam, width, height);
        }
        break;

    case WM_PAINT:
        {
            PAINTSTRUCT sPaint;
            HDC hdc = BeginPaint(m_hwnd, &sPaint);

            /** Begin painting... */

            FillRect(hdc, &sPaint.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            /** ...end painting. */

            EndPaint(m_hwnd, &sPaint);
        }
        return 0;

    default:

        return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }

    return TRUE;
}
