/***************************************************************************//**
 * @file win32_resource.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-09-01
 *
 * @copyright
 *
 ******************************************************************************/
#pragma once

#define _WIN32_RESOURCE_H_

#ifndef __RC_RESOURCE_T
/**
 * The underlying 'RCRESOURCE' typedef; maps a simple datatype to the 'RCRESOURCE'
 * typedef. Can be over-ridden to other data types, for example by specifying
 * "-D__RC_RESOURCE_T='some new data type'" or similar when building.
 *
 */
#define __RC_RESOURCE_T const signed char
/** The 'RCRESOURCE' type; maps a simple datatype to the 'RCRESOURCE'
 * typedef. Can be over-ridden to other data types, for example by specifying
 * "-D__RC_RESOURCE_T='some new data type'" or similar when building..
 *
*/
typedef __RC_RESOURCE_T RCRESOURCE;
#endif //

/** The underlying 'RCRESOURCEPTR' type; wraps a raw pointer to the 'RESOURCE' typedef. */
#define __RC_RESOURCE_T_PTR RCRESOURCE*
/** The 'RESOURCEPTR' type; wraps a raw pointer to the 'RESOURCE' typedef. */
typedef __RC_RESOURCE_T_PTR RCRESOURCEPTR;

#include "cmrc.hpp"

#define __FS_EMBEDDED CMakeRC::EmbeddedFileSystem
typedef __FS_EMBEDDED FSEMBEDDED;

#define __RES_IDX_T CMakeRC::Detail::IndexType
typedef __RES_IDX_T IDXRES;

#include "img/win32_png.hpp"

#include "img/win32_ApplicationIcon_png.hpp"
#include "img/win32_Logo_png.hpp"
#include "img/win32_SmallLogo_png.hpp"
#include "img/win32_SmallLogo44x44_png.hpp"
#include "img/win32_SplashScreen_png.hpp"
#include "img/win32_StoreLogo_png.hpp"

#include "key/win32_pfx.hpp"

#include "key/win32_Windows_TemporaryKey_pfx.hpp"
