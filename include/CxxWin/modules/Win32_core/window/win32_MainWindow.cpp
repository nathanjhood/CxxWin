/***************************************************************************//**
 * @file win32_MainWindow.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Contains a definition of the 'MainWindow' class which inherits from
 * the 'BaseWindow' class. Inherit this 'MainWindow' class for a basic window
 * functionality.
 *
 * @version 1.0.0
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

/**
 * @brief
 *
 * @return PCWSTR
 */
PCWSTR MainWindow::ClassName() CONST
{
    return TEXT("UDEFINED");
}

/**
 * @brief
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
        case WM_DESTROY:

            // Destroy 'WinMain()'? So be it...
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(m_hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
            EndPaint(m_hwnd, &ps);
        }
        return 0;

        default:
            return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
    }
    return TRUE;
}
