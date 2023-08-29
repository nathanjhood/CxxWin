#pragma once
/***************************************************************************//**
 * @file Main.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-23
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#define MAIN_H

#ifndef WINVER
#  define WINVER 0x0A00
#endif

#ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x0A00
#endif

#ifdef D2D_USE_C_DEFINITIONS
#  undef D2D_USE_C_DEFINITIONS
#endif

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#if !defined(UNICODE) || !defined(_UNICODE)
int WINAPI WinMain  (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
#else
int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd);
#endif

#ifdef RC_INVOKED
#include "resource.h"

VS_VERSION_INFO			VERSIONINFO
FILEVERSION				1,0,0,0
PRODUCTVERSION 			1,0,0,0
FILEFLAGSMASK 			VS_FFI_FILEFLAGSMASK
#ifdef _DEBUG
	FILEFLAGS			VS_FF_DEBUG | VS_FF_PRERELEASE
#else
	FILEFLAGS			0
#endif
FILEOS 					VOS_NT_WINDOWS32
FILETYPE 				VFT_APP
FILESUBTYPE 			VFT2_UNKNOWN
BEGIN
	BLOCK "StringFileInfo"
	BEGIN
		BLOCK "080904b0"
		BEGIN
			VALUE "CompanyName", "StoneyDSP"
			VALUE "FileDescription", "Win32 API from C++."
			VALUE "FileVersion", "1.0.0.0"
			VALUE "InternalName", "CxxWin"
			VALUE "LegalCopyright", "Copyright (c) 2023 Nathan J. Hood (nathanjhood@googlemail.com)"
			VALUE "OriginalFilename", "executable.exe"
			VALUE "ProductName", "CxxWin"
			VALUE "ProductVersion", "1.0.0.0"
		END
	END
	BLOCK "VarFileInfo"
	BEGIN
		VALUE "Translation", 0x809, 1200
	END
END

CREATEPROCESS_MANIFEST_RESOURCE_ID RT_MANIFEST "CxxWin-ucrt64.exe.manifest"
#endif // RC_INVOKED
