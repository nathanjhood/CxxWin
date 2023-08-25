#include "../cmrc.hpp"
#include <map>
#include <utility>

namespace cmrc {
namespace img {
/** These are the files which are available in this resource library */
namespace res_chars {
/** Pointers to ApplicationIcon.png */
extern const char* const f_e1be_ApplicationIcon_png_begin;
extern const char* const f_e1be_ApplicationIcon_png_end;
/** Pointers to Logo.png */
extern const char* const f_c9c2_Logo_png_begin;
extern const char* const f_c9c2_Logo_png_end;
/** Pointers to SmallLogo.png */
extern const char* const f_21a7_SmallLogo_png_begin;
extern const char* const f_21a7_SmallLogo_png_end;
/** Pointers to SmallLogo44x44.png */
extern const char* const f_77be_SmallLogo44x44_png_begin;
extern const char* const f_77be_SmallLogo44x44_png_end;
/** Pointers to SplashScreen.png */
extern const char* const f_4e97_SplashScreen_png_begin;
extern const char* const f_4e97_SplashScreen_png_end;
/** Pointers to StoreLogo.png */
extern const char* const f_7748_StoreLogo_png_begin;
extern const char* const f_7748_StoreLogo_png_end;
}

namespace {

const cmrc::detail::index_type&
get_root_index() {
    static cmrc::detail::directory root_directory_;
    static cmrc::detail::file_or_directory root_directory_fod{root_directory_};
    static cmrc::detail::index_type root_index;
    root_index.emplace("", &root_directory_fod);
    struct dir_inl {
        class cmrc::detail::directory& directory;
    };
    dir_inl root_directory_dir{root_directory_};
    (void)root_directory_dir;

    root_index.emplace(
        "ApplicationIcon.png",
        root_directory_dir.directory.add_file(
            "ApplicationIcon.png",
            res_chars::f_e1be_ApplicationIcon_png_begin,
            res_chars::f_e1be_ApplicationIcon_png_end
        )
    );
    root_index.emplace(
        "Logo.png",
        root_directory_dir.directory.add_file(
            "Logo.png",
            res_chars::f_c9c2_Logo_png_begin,
            res_chars::f_c9c2_Logo_png_end
        )
    );
    root_index.emplace(
        "SmallLogo.png",
        root_directory_dir.directory.add_file(
            "SmallLogo.png",
            res_chars::f_21a7_SmallLogo_png_begin,
            res_chars::f_21a7_SmallLogo_png_end
        )
    );
    root_index.emplace(
        "SmallLogo44x44.png",
        root_directory_dir.directory.add_file(
            "SmallLogo44x44.png",
            res_chars::f_77be_SmallLogo44x44_png_begin,
            res_chars::f_77be_SmallLogo44x44_png_end
        )
    );
    root_index.emplace(
        "SplashScreen.png",
        root_directory_dir.directory.add_file(
            "SplashScreen.png",
            res_chars::f_4e97_SplashScreen_png_begin,
            res_chars::f_4e97_SplashScreen_png_end
        )
    );
    root_index.emplace(
        "StoreLogo.png",
        root_directory_dir.directory.add_file(
            "StoreLogo.png",
            res_chars::f_7748_StoreLogo_png_begin,
            res_chars::f_7748_StoreLogo_png_end
        )
    );
    return root_index;
}

}

cmrc::embedded_filesystem get_filesystem() {
    static auto& index = get_root_index();
    return cmrc::embedded_filesystem{index};
}

} /** img */
} /** cmrc */
