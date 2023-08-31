/**
 * @file win32_Unicode.h
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-31
 *
 * @copyright Copyright (c) 2023
 *
 */

#if !defined(_INC_CRT_UNICODE_MACROS)
/* _INC_CRT_UNICODE_MACROS defined based on UNICODE flag */

#if defined(UNICODE)
# define _INC_CRT_UNICODE_MACROS 1
# define __NAME_AW(func) func##W
# define __NAME_AW_EXT(func,ext) func##W##ext
# define __NAME_UAW(func) func##_W
# define __NAME_UAW_EXT(func,ext) func##_W_##ext
# define __STRING_AW(str) L##str	/* same as TEXT() from winnt.h */
# define __PROCNAMEEXT_AW "W"
#else
# define _INC_CRT_UNICODE_MACROS 2
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

#endif /* !defined(_INC_CRT_UNICODE_MACROS) */
