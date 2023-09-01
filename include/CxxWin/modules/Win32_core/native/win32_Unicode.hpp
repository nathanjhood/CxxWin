/***************************************************************************//**
 * @file win32_Unicode.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Provides preprocessor handling for switching the behaviour of some
 * important functions such as 'TEXT()', between 'ANSI' and 'Unicode' styles.
 *
 * @version 1.0.0-init
 * @date 2023-08-31
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/
#pragma once
/**
 *  @brief Provides preprocessor handling for switching the behaviour of some
 * important functions such as 'TEXT()', between 'ANSI' and 'Unicode' styles.
 */
#define _WIN32_UNOCIDE_HPP_

#if !defined(_NEED_UNICODE)
/* _NEED_UNICODE defined based on UNICODE flag */

#if defined(UNICODE)
# define _NEED_UNICODE 1
# define __NAME_AW(func) func##W
# define __NAME_AW_EXT(func,ext) func##W##ext
# define __NAME_UAW(func) func##_W
# define __NAME_UAW_EXT(func,ext) func##_W_##ext
# define __STRING_AW(str) L##str	/* same as TEXT() from winnt.h */
# define __PROCNAMEEXT_AW "W"
#else
# define _NEED_UNICODE 2
# define __NAME_AW(func) func##A
# define __NAME_AW_EXT(func,ext) func##A##ext
# define __NAME_UAW(func) func##_A
# define __NAME_UAW_EXT(func,ext) func##_A_##ext
# define __STRING_AW(str) str	/* same as TEXT() from winnt.h */
# define __PROCNAMEEXT_AW "A"
#endif

#define __TYPEDEF_AW(type)	\
    typedef __NAME_AW(type) type;
#define __TYPEDEF_UAW(type)	\
    typedef __NAME_UAW(type) type;

#endif /* !defined(_NEED_UNICODE) */

/** The generic function prototype uses the data type LPCTSTR. */
WINUSERAPI LPCTSTR WINAPI SetTst(LPCTSTR lpString) { return lpString; };

auto unicodeTstA = SetTst(TEXT("Calling original function"));

/**
 * The header file provides the generic function name implemented as a macro.
 * The preprocessor expands the macro into either the Windows code page or
 * Unicode function name. The letter "A" (ANSI) or "W" (Unicode) is added at
 * the end of the generic function name, as appropriate. The header file then
 * provides two specific prototypes, one for Windows code pages and one for
 * Unicode.
 *
 * #if defined(UNICODE)
 * #define SetTst SetTstW
 * #else
 * #define SetTst SetTstA
 * #endif
 *
 * @link https://learn.microsoft.com/en-us/windows/win32/intl/conventions-for-function-prototypes
 *
 */
#define SetTst __NAME_AW(SetTst)

/** The Windows code page prototype uses the data type LPCSTR. */
WINUSERAPI LPCSTR WINAPI SetTstA(LPCSTR lpString) { return lpString; };
/** The Unicode prototype uses the data type LPCWSTR. */
WINUSERAPI LPCWSTR WINAPI SetTstW(LPCWSTR lpString) { return lpString; };

auto unicodeTstB = SetTst(TEXT("Calling corrected function"));
