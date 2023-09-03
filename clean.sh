#!/usr/bin/env sh

cxxwin_clean_msystem_set_lower_case ()
{
	case "${MSYSTEM}" in
		MINGW32)
			_msystem="mingw32"
			export _msystem
			;;
		MINGW64)
			_msystem="mingw64"
			export _msystem
			;;
		CLANG32)
			_msystem="clang32"
			export _msystem
			;;
		CLANG64)
			_msystem="clang64"
			export _msystem
			;;
		CLANGARM64)
			_msystem="clangarm64"
			export _msystem
			;;
		UCRT64)
			_msystem="ucrt64"
			export _msystem
			;;
		*)
			_msystem="usr"
			export _msystem
			;;
	esac
}

cxxwin_clean_output_dir ()
{
	rm -rvf ./out/${_msystem}
}

cxxwin_clean_msystem_set_lower_case
cxxwin_clean_output_dir

unset \
	_msystem \
	cxxwin_clean_msystem_set_lower_case \
	cxxwin_clean_output_dir
