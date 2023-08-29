#pragma once
/**
 * @file win32_SmartPointer.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#define WIN32_SMARTPOINTER_H

/**
 * @brief
 *
 * @tparam T
 * @param ppT
 */
template <class T>
void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}
