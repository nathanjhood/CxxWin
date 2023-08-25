#include "../cmrc.hpp"
#include <map>
#include <utility>

namespace cmrc {
namespace key {

namespace res_chars {
// These are the files which are available in this resource library
// Pointers to Windows_TemporaryKey.pfx
extern const char* const f_8c2e_Windows_TemporaryKey_pfx_begin;
extern const char* const f_8c2e_Windows_TemporaryKey_pfx_end;
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
        "Windows_TemporaryKey.pfx",
        root_directory_dir.directory.add_file(
            "Windows_TemporaryKey.pfx",
            res_chars::f_8c2e_Windows_TemporaryKey_pfx_begin,
            res_chars::f_8c2e_Windows_TemporaryKey_pfx_end
        )
    );
    return root_index;
}

}

cmrc::embedded_filesystem get_filesystem() {
    static auto& index = get_root_index();
    return cmrc::embedded_filesystem{index};
}

} // key
} // cmrc
