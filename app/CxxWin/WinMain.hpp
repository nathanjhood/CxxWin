/***************************************************************************//**
 * @file WinMain.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Contains the declarations of 'WinMain'.
 *
 * @version 1.0.0
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once
/** Contains the declarations of 'WinMain'. */
#define _WINMAIN_HPP_

#include "MainComponent.hpp"

// Switch entry point definition between 'ANSI' and 'Unicode' types.
#if !defined(UNICODE) || !defined(_UNICODE)
typedef LPSTR LPCMDLINE;
/** Contains the ANSI-style declaration of 'WinMain'. */
#define WinMain WinMain
#else
typedef LPWSTR LPCMDLINE;
/** Contains the Unicode-style declaration of 'WinMain'. */
#define WinMain wWinMain
#endif // UNICODE
