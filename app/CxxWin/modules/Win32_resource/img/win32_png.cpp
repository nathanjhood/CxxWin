/***************************************************************************//**
 * @file win32_png.cpp
 * @author StoneyDSP (nathanjhood@googlemail.com)
 *
 * @brief Contains pointers to named resources with external linkage, so that
 * their respective contents can be defined elsewhere. Also contains definitions
 * of functions that provide access to these specifically-named resources, which
 * necessitates external linkage.
 *
 * @version 1.0.0
 * @date 2023-08-24
 *
 * @copyright This file was generated by using Vector-of-Bool's excellent
 * 'CMakeRC' resource compiler script from CMake's template resources for
 * Windows. The results have been given minimal tweaks - mostly just text
 * formatting - to provide a similar interface to the rest of the project's
 * codebase. Please see 'cmrc.hpp' and Kitware.org for respective license
 * information.
 *
 ******************************************************************************/

#include "win32_png.hpp"

namespace CMakeRC
{
namespace Img
{
namespace ApplicationIcon
{
/** @brief Pointer to the beginning of 'ApplicationIcon_png_array'. */
extern RCRESOURCEPTR const ApplicationIcon_png_begin;
/** @brief Pointer to the end of 'ApplicationIcon_png_array'. */
extern RCRESOURCEPTR const ApplicationIcon_png_end;
}
namespace Logo
{
/** @brief Pointer to the beginning of 'Logo_png_array'. */
extern RCRESOURCEPTR const Logo_png_begin;
/** @brief Pointer to the end of 'Logo_png_array'. */
extern RCRESOURCEPTR const Logo_png_end;
}
namespace SmallLogo
{
/** @brief Pointer to the beginning of 'SmallLogo_png_array'. */
extern RCRESOURCEPTR const SmallLogo_png_begin;
/** @brief Pointer to the end of 'SmallLogo_png_array'. */
extern RCRESOURCEPTR const SmallLogo_png_end;
}
namespace SmallLogo44x44
{
/** @brief Pointer to the beginning of 'SmallLogo44x44_png_array'. */
extern RCRESOURCEPTR const SmallLogo44x44_png_begin;
/** @brief Pointer to the end of 'SmallLogo44x44_png_array'.*/
extern RCRESOURCEPTR const SmallLogo44x44_png_end;
}
namespace SplashScreen
{
/** @brief Pointer to the beginning of 'SplashScreen_png_array'. */
extern RCRESOURCEPTR const SplashScreen_png_begin;
/** @brief Pointer to the end of 'SplashScreen_png_array'. */
extern RCRESOURCEPTR const SplashScreen_png_end;
}
namespace StoreLogo
{
/** @brief Pointer to the beginning of 'StoreLogo_png_array'. */
extern RCRESOURCEPTR const StoreLogo_png_begin;
/** @brief Pointer to the end of 'StoreLogo_png_array'. */
extern RCRESOURCEPTR const StoreLogo_png_end;
}

namespace
{
/**
 * @brief Get the 'CMakeRC::Detail::IndexType' object.
 *
 * @return const 'CMakeRC::Detail::IndexType' &
 */
const IDXRES& GetRootIndex()
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
            ApplicationIcon::ApplicationIcon_png_begin,
            ApplicationIcon::ApplicationIcon_png_end
        )
    );
    root_index.emplace
    (
        "Logo.png",
        root_directory_dir.Directory.AddFile
        (
            "Logo.png",
            Logo::Logo_png_begin,
            Logo::Logo_png_end
        )
    );
    root_index.emplace
    (
        "SmallLogo.png",
        root_directory_dir.Directory.AddFile
        (
            "SmallLogo.png",
            SmallLogo::SmallLogo_png_begin,
            SmallLogo::SmallLogo_png_end
        )
    );
    root_index.emplace
    (
        "SmallLogo44x44.png",
        root_directory_dir.Directory.AddFile
        (
            "SmallLogo44x44.png",
            SmallLogo44x44::SmallLogo44x44_png_begin,
            SmallLogo44x44::SmallLogo44x44_png_end
        )
    );
    root_index.emplace
    (
        "SplashScreen.png",
        root_directory_dir.Directory.AddFile
        (
            "SplashScreen.png",
            SplashScreen::SplashScreen_png_begin,
            SplashScreen::SplashScreen_png_end
        )
    );
    root_index.emplace
    (
        "StoreLogo.png",
        root_directory_dir.Directory.AddFile
        (
            "StoreLogo.png",
            StoreLogo::StoreLogo_png_begin,
            StoreLogo::StoreLogo_png_end
        )
    );
    return root_index;
}

} // namespace

/**
 * @brief Get the 'CMakeRC::EmbeddedFileSystem' 'CMakeRC::Detail::IndexType'
 * object.
 *
 * @return 'FSEMBEDDED'
 */
FSEMBEDDED GetFileSystem()
{
    static auto& index = GetRootIndex();
    return CMakeRC::EmbeddedFileSystem{index};
}

} // namespace Img
} // namespace CMakeRC