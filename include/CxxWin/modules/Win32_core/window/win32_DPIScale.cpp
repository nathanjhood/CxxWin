/***************************************************************************//**
 * @file win32_DPIScale.cpp
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

/**
 * @brief The 'Initialize' function.
 *
 * @param pFactory
 */
void DPIScale::Initialize(ID2D1Factory* pFactory)
{
    FLOAT dpiX, dpiY, res;

    res = 96.0F;

    pFactory->GetDesktopDpi(&dpiX, &dpiY);

    scaleX = dpiX / res;
    scaleY = dpiY / res;
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
D2D1_POINT_2F DPIScale::PixelsToDips(T x, T y)
{
    return D2D1::Point2F(static_cast<FLOAT>(x) / scaleX, static_cast<FLOAT>(y) / scaleY);
}

/**
 * @brief DPI-scaled position X co-ordinate.
 *
 */
FLOAT DPIScale::scaleX = { 1.0F };

/**
 * @brief DPI-scaled position Y co-ordinate.
 *
 */
FLOAT DPIScale::scaleY = { 1.0F };
