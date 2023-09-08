/***************************************************************************//**
 * @file win32_DPIScale.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Contains the 'DPIScale' class.
 *
 * @version 1.0.0
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once

/** @brief Contains the 'DPIScale' class. */
#define _WIN32_DPISCALE_HPP_

// namespace Win32
// {
// namespace Core
// {
// namespace Window
// {
/**
 * @brief The 'DPIScale' class.
 *
 */
class DPIScale
{
public:
    static void Initialize(ID2D1Factory* pFactory);

    template <typename T>
    static D2D1_POINT_2F PixelsToDips(T x, T y);

private:
    static FLOAT scaleX;
    static FLOAT scaleY;
};

/** @brief The 'DPIScale' datatype. */
#define _DPIScale_T DPIScale
/** @brief The 'DPIScale' datatype. */
typedef class _DPIScale_T DPIScale;

// } // namespace Window
// } // namespace Core
// } // namespace Win32
