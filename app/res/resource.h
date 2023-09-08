#pragma once

#include <winres.h>
#include <windows.h>
#include <ole2.h>

#include <winuser.rh>
#include <commctrl.rh>
#include <dde.rh>
#include <winnt.rh>
#include <dlgs.h>
#include <winver.h>

//<SnippetResource_H>
#ifndef BEGIN
#  define BEGIN {
#endif

#ifndef END
#  define END }
#endif

// #if defined(RC_INVOKED)

    #define IDI_APPICON 101
    #define IDR_MAIN_MENU 102
    #define IDR_ACCELERATOR 103
    #define IDD_ABOUTDIALOG 104

    #define ID_FILE_EXIT 40001
    #define ID_HELP_ABOUT 40002

    #ifndef IDC_STATIC
    #  define IDC_STATIC -1
    #endif

// #else

//     #define IDI_APPICON MAKEINTRESOURCE(101)
//     #define IDR_MAIN_MENU MAKEINTRESOURCE(102)
//     #define IDR_ACCELERATOR MAKEINTRESOURCE(103)
//     #define IDD_ABOUTDIALOG MAKEINTRESOURCE(104)

//     #define ID_FILE_EXIT MAKEINTRESOURCE(40001)
//     #define ID_HELP_ABOUT MAKEINTRESOURCE(40002)

//     #ifndef IDC_STATIC
//     #  define IDC_STATIC MAKEINTRESOURCE(-1)
//     #endif

// #endif
//<SnippetResource_H>
