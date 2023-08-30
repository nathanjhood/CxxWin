/***************************************************************************//**
 * @file png.cpp
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
namespace Img
{
/** These are the files which are available in this resource library */
namespace res_chars
{

extern const char* const ApplicationIcon_png_begin;
extern const char* const ApplicationIcon_png_end;

extern const char* const Logo_png_begin;
extern const char* const Logo_png_end;

/** Pointers to SmallLogo.png */
extern const char* const SmallLogo_png_begin;
extern const char* const SmallLogo_png_end;

/** Pointers to SmallLogo44x44.png */
extern const char* const SmallLogo44x44_png_begin;
extern const char* const SmallLogo44x44_png_end;

/** Pointers to SplashScreen.png */
extern const char* const SplashScreen_png_begin;
extern const char* const SplashScreen_png_end;

/** Pointers to StoreLogo.png */
extern const char* const StoreLogo_png_begin;
extern const char* const StoreLogo_png_end;
}

namespace
{
/**
 * @brief Get the root index object
 *
 * @return const CMakeRC::detail::IndexType&
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

    root_index.emplace
    (
        "ApplicationIcon.png",
        root_directory_dir.Directory.AddFile
        (
            "ApplicationIcon.png",
            res_chars::ApplicationIcon_png_begin,
            res_chars::ApplicationIcon_png_end
        )
    );
    root_index.emplace
    (
        "Logo.png",
        root_directory_dir.Directory.AddFile
        (
            "Logo.png",
            res_chars::Logo_png_begin,
            res_chars::Logo_png_end
        )
    );
    root_index.emplace
    (
        "SmallLogo.png",
        root_directory_dir.Directory.AddFile
        (
            "SmallLogo.png",
            res_chars::SmallLogo_png_begin,
            res_chars::SmallLogo_png_end
        )
    );
    root_index.emplace
    (
        "SmallLogo44x44.png",
        root_directory_dir.Directory.AddFile
        (
            "SmallLogo44x44.png",
            res_chars::SmallLogo44x44_png_begin,
            res_chars::SmallLogo44x44_png_end
        )
    );
    root_index.emplace
    (
        "SplashScreen.png",
        root_directory_dir.Directory.AddFile
        (
            "SplashScreen.png",
            res_chars::SplashScreen_png_begin,
            res_chars::SplashScreen_png_end
        )
    );
    root_index.emplace
    (
        "StoreLogo.png",
        root_directory_dir.Directory.AddFile
        (
            "StoreLogo.png",
            res_chars::StoreLogo_png_begin,
            res_chars::StoreLogo_png_end
        )
    );
    return root_index;
}

} /** namespace <unnamed> */

/**
 * @brief Get the 'EmbeddedFileSystem' object
 *
 * @return CMakeRC::EmbeddedFileSystem
 */
CMakeRC::EmbeddedFileSystem GetFileSystem()
{
    static auto& index = GetRootIndex();
    return CMakeRC::EmbeddedFileSystem{index};
}

} /** namespace Img */
} /** namespace CMakeRC */
