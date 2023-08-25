/**
 * @file CxxWin/BaseWindow.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _CXX_WIN_BASE_WINDOW_H_
#define _CXX_WIN_BASE_WINDOW_H_

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#ifndef WINVER
#  define WINVER 0x0A00
#endif

#ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x0A00
#endif

#include <windows.h>
/** WIN32_LEAN_AND_MEAN */

struct StateInfo
{
    int x = CW_USEDEFAULT;
    int y = CW_USEDEFAULT;
    int nWidth = CW_USEDEFAULT;
    int nHeight = CW_USEDEFAULT;
};

inline StateInfo* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);

    StateInfo *pState = reinterpret_cast<StateInfo*>(ptr);

    return pState;
}

template <class DERIVED_TYPE>
class BaseWindow
{
public:

    BaseWindow() : m_hwnd(NULL)
    {
        /** Constructor (w/Initializer list) */
    }

    /**
     * @brief 'LRESULT' is an integer value that your program returns to Windows.
     * It contains your program's response to a particular message. The meaning of
     * this value depends on the message code.
     *
     * @param hwnd is a handle to the window.
     * @param uMsg is the message code; for example, the WM_SIZE message indicates
     * the window was resized.
     * @param wParam contains additional code-dependent data about the message.
     * @param lParam contains additional code-dependent data about the message.
     * @return 'LRESULT'
     */
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        StateInfo *pState;

        if (uMsg == WM_CREATE)
        {
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pState = reinterpret_cast<StateInfo*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pState);
        }
        else
        {
            pState = GetAppState(hwnd);
        }

        DERIVED_TYPE *pThis = NULL;

        /**
         * 'WM_NC*' definitions refer to 'non-client' events,
         * i.e., mouse clicks outside of the app window. etc.
         */
        if (uMsg == WM_NCCREATE)
        {
            CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
            pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);

            pThis->m_hwnd = hwnd;
        }
        else
        {
            pThis = (DERIVED_TYPE*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
        }

        if (pThis)
        {
            return pThis->HandleMessage(uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    BOOL Create(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle = 0, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, int nHeight = CW_USEDEFAULT, HWND hWndParent = 0, HMENU hMenu = 0)
    {
        /** Initiate a window class */
        WNDCLASS wc = {0};

        /** Enable mouse double-clicks on the window...*/
        wc.style = CS_DBLCLKS;

        wc.lpfnWndProc   = DERIVED_TYPE::WindowProc;
        wc.hInstance     = GetModuleHandle(NULL);
        wc.lpszClassName = ClassName();

        RegisterClass(&wc);

        m_hwnd = CreateWindowEx(dwExStyle, ClassName(), lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, GetModuleHandle(NULL), this);

        return (m_hwnd ? TRUE : FALSE);
    }

    HWND Window() CONST { return m_hwnd; }

protected:

    virtual PCWSTR  ClassName() CONST PURE;

    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) PURE;

    HWND m_hwnd;
};

#endif /** _CXX_WIN_BASEWINDOW_H_ */
