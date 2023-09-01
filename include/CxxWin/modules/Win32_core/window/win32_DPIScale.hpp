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

/**
 * @brief The 'DPIScale' class.
 *
 */
class DPIScale
{
public:
    /**
     * @brief The 'Initialize' function.
     *
     * @param pFactory
     */
    static void Initialize(ID2D1Factory* pFactory)
    {
        FLOAT dpiX, dpiY;
        pFactory->GetDesktopDpi(&dpiX, &dpiY);
        scaleX = dpiX / 96.0F;
        scaleY = dpiY / 96.0F;
    }

    /**
     * @brief Pixels to DIP's.
     *
     * @tparam T
     * @param x
     * @param y
     * @return D2D1_POINT_2F
     */
    template <typename T>
    static D2D1_POINT_2F PixelsToDips(T x, T y)
    {
        return D2D1::Point2F(static_cast<FLOAT>(x) / scaleX, static_cast<FLOAT>(y) / scaleY);
    }

private:
    static FLOAT scaleX;
    static FLOAT scaleY;
};
