/***************************************************************************//**
 * @file win32_ApplicationIcon_png.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Contains a default declaration of 'ApplicationIcon_png_array' (see
 * 'copyright' section).
 *
 * @version 1.0.0-init
 * @date 2023-08-24
 *
 * @copyright This file was generated by using Vector-of-Bool's excellent
 * 'CMakeRC' resource compiler script from CMake's template resources for
 * Windows. The results have been given minimal tweaks - mostly just text
 * formatting - to provide a similar interface to the rest of the project's
 * codebase. Please see 'cmrc.hpp' and Kitware.org for respective license
 * information.
 *
 * @see 'ApplicationIcon.png'
 *
 ******************************************************************************/
#pragma once
/**
 * @brief Contains a default declaration of 'ApplicationIcon_png_array' (see
 * 'copyright' section).
 *
 */
#define _WIN32_RESOURCE_IMG_APPLICATION_ICON_PNG_HPP_

namespace
{
/**
 * @brief An array of bytes representing "ApplicationIcon.png".
 *
 * @see 'ApplicationIcon.png'
 *
 */
RCRESOURCE ApplicationIcon_png_array[2336];
} // namespace

namespace CMakeRC::Img
{
/**
 * @namespace 'CMakeRC::Img::ApplicationIcon'
 *
 * @brief The 'ApplicationIcon' namespace. Contains declarations and definitions
 * of binary-compiled 'ApplicationIcon.png' for interacting with Win32 API.
 *
 */
namespace ApplicationIcon
{
/** @brief Pointer to the beginning of 'ApplicationIcon_png_array'. */
extern RCRESOURCEPTR const ApplicationIcon_png_begin;
/** @brief Pointer to the end of 'ApplicationIcon_png_array'. */
extern RCRESOURCEPTR const ApplicationIcon_png_end;
} // namespace Img::ApplicationIcon
} // namespace CMakeRC
