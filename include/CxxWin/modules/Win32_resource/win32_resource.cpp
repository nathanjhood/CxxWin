/***************************************************************************//**
 * @file win32_resource.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-09-01
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#ifdef _WIN32_RESOURCE_H_
#  error "Incorrect useage of .cpp file!"
#endif

#include "win32_resource.hpp"

#include "img/win32_png.cpp"

#include "img/win32_ApplicationIcon_png.cpp"
#include "img/win32_Logo_png.cpp"
#include "img/win32_SmallLogo_png.cpp"
#include "img/win32_SmallLogo44x44_png.cpp"
#include "img/win32_SplashScreen_png.cpp"
#include "img/win32_StoreLogo_png.cpp"

#include "key/win32_pfx.cpp"

#include "key/win32_Windows_TemporaryKey_pfx.cpp"
