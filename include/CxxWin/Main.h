/***************************************************************************//**
 * @file Main.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief Contains the declarations of 'Main'.
 * @version 1.0.0-init
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#pragma once
/** Contains the declarations of 'Main'. */
#define __MAIN_H


#include "MainComponent.h"

#if !defined(UNICODE) || !defined(_UNICODE)
int WINAPI WinMain  (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
#else
int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);
#endif
