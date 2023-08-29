/**
 * @file Mouse.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-28
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "Mouse.h"

Mouse::Mouse()
 : _b_MouseTracking(false)
{

}

Mouse::Mouse(bool enableTracking = false)
 : _b_MouseTracking(enableTracking)
{

}

Mouse::~Mouse()
{

}

void Mouse::OnMouseMove(HWND hwnd)
{
    if (!(_b_MouseTracking))
    {
        /** Enable Mouse tracking. */
        TRACKMOUSEEVENT tme;
        tme.cbSize = sizeof(tme);
        tme.hwndTrack = hwnd;
        tme.dwFlags = TME_HOVER | TME_LEAVE;
        tme.dwHoverTime = HOVER_DEFAULT;
        TrackMouseEvent(&tme);
        _b_MouseTracking = true;
    }
}

void Mouse::Reset(HWND hwnd)
{
    _b_MouseTracking = false;
}

UINT Mouse::GetMouseHoverTime()
{
    UINT msec = {0};
    HRESULT hr = SystemParametersInfo(SPI_GETMOUSEHOVERTIME, 0, &msec, 0);
    if (SUCCEEDED(hr))
    {
        return msec;
    }
    else
    {
        return 0;
    }
}
