/***************************************************************************//**
 * @file pfx.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 * @brief
 * @version 1.0.0-init
 * @date 2023-08-24
 *
 * @copyright Copyright (c) 2023
 *
 ******************************************************************************/

#include <map>
#include <utility>

#include "../cmrc.hpp"

namespace CMakeRC
{
namespace Key
{
/** These are the files which are available in this resource library */
namespace res_chars
{
// Pointers to Windows_TemporaryKey.pfx
extern const char* const Windows_TemporaryKey_pfx_begin;
extern const char* const Windows_TemporaryKey_pfx_end;
}

namespace
{
/**
 * @brief Get the root index object
 *
 * @return const CMakeRC::Detail::IndexType&
 */
const CMakeRC::Detail::IndexType& GetRootIndex()
{
    static CMakeRC::Detail::Directory root_directory_;
    static CMakeRC::Detail::FileOrDirectory root_directory_fod{root_directory_};
    static CMakeRC::Detail::IndexType root_index;
    root_index.emplace("", &root_directory_fod);

    struct dir_inl
    {
        class CMakeRC::Detail::Directory& Directory;
    };

    dir_inl root_directory_dir{root_directory_};
    (void)root_directory_dir;

    root_index.emplace(
        "Windows_TemporaryKey.pfx",
        root_directory_dir.Directory.AddFile(
            "Windows_TemporaryKey.pfx",
            res_chars::Windows_TemporaryKey_pfx_begin,
            res_chars::Windows_TemporaryKey_pfx_end
        )
    );
    return root_index;
}

} /** namespace <unnamed> */

/**
 * @brief Get the 'EmbeddedFileSystem' object
 *
 * @namespace CMakeRC
 * @namespace Img
 * @return CMakeRC::EmbeddedFileSystem
 */
CMakeRC::EmbeddedFileSystem GetFileSystem()
{
    static auto& index = GetRootIndex();
    return CMakeRC::EmbeddedFileSystem{index};
}

} /** namespace Key */
} /** namespace CMakeRC */
