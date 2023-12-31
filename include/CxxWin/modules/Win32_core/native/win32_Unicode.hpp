/***************************************************************************//**
 * @file win32_Unicode.hpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Provides preprocessor handling for switching the behaviour of some
 * important functions such as 'TEXT()', between 'ANSI' and 'Unicode' styles.
 *
 * @version 1.0.0
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

namespace Win32
{
namespace Core
{
namespace Native
{
class UnicodeHandler
{
public:
    BOOL SetVar(HWND hwnd, LPCTSTR lpText);

    BOOL SetVarA(HWND hwnd, LPCSTR lpText);

    BOOL SetVarW(HWND hwnd, LPCWSTR lpText);
};

}
}
}
