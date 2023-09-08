#!/usr/bin/env sh

# Once sourced, this script provides common information associated with the
# current MSYSTEM. For example, the compiler architecture and host type.

# The MSYSTEM_ prefix is used for avoiding too generic names. For example,
# makepkg is sensitive to the value of CARCH, so MSYSTEM_CARCH is defined
# instead. The MINGW_ prefix does not influence makepkg-mingw variables and
# is not used for the MSYS shell.

msystem_toolchain_configure ()
{

	# Parts of this function are adapted from the following:
	# MSYSTEM Environment Information
	# Copyright (C) 2016 Renato Silva
	# Licensed under public domain

	# Flags
	# -march (or -mcpu) builds exclusively for an architecture
	# -mtune optimizes for an architecture, but builds for whole processor family

	if [[ "${MSYSTEM}" == "" ]]; then
		export MSYSTEM="${MSYSTEM:-MSYS}"
	fi

	unset MSYSTEM_PREFIX
	unset MSYSTEM_CARCH
	unset MSYSTEM_CHOST

	unset MINGW_CHOST
	unset MINGW_PREFIX
	unset MINGW_PACKAGE_PREFIX

	# Set the install location to prefix all absolute paths for compilers, etc.
	unset MSYS_INSTALL_PATH
	MSYS_INSTALL_PATH="C:/msys64"

	# Boolean to control which BinUtils to choose from.
	#
	# if DXMODE=0, then BinUtils will be '$(msys_install_path)/$(msystem_prefix)/bin/*.exe'
	# else if DXMODE=1, then BinUtils will be '$(msys_install_path)/$(dxsdk_dir)/bin/*.exe'
	unset DX_MODE
	DX_MODE=1

	case "${MSYSTEM}" in
		MINGW32)
			# Platform
			CARCH="i686"
			CHOST="i686-w64-mingw32"
			COMPILER_NAME="GNU"
			COMPILER_VERSION="13.2.0"
			NPROCS="-j$(($(/usr/bin/nproc)+1))"
			# Variables
			MSYSTEM_PREFIX='/mingw32'
			MSYSTEM_CARCH='i686'
			MSYSTEM_CHOST='i686-w64-mingw32'
			MINGW_CHOST="${MSYSTEM_CHOST}"
			MINGW_PREFIX="${MSYSTEM_PREFIX}"
			MINGW_PACKAGE_PREFIX="mingw-w64-${MSYSTEM_CARCH}"
			# DirectX compatibility environment variable
			DXSDK_DIR=${MSYSTEM_PREFIX}/${MSYSTEM_CHOST}
			if [[ "$DX_MODE" == 1 ]]; then
				BINUTILS_PATH="${DXSDK_DIR}"
			else
				BINUTILS_PATH="${MSYSTEM_PREFIX}"
			fi
			# BinUtils
			AR="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ar.exe"
			AS="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/as.exe"
			LD="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ld.exe"
			NM="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/nm.exe"
			DLLTOOL="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/dlltool.exe"
			RANLIB="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ranlib.exe"
			READELF="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/readelf.exe"
			OBJCOPY="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/objcopy.exe"
			OBJDUMP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/objdump.exe"
			STRIP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/strip.exe"
			# Compilers
			RC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/windres.exe"
			CC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-gcc.exe"
			CXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-g++.exe"
			OBJCC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-gcc.exe"
			OBJCXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-g++.exe"
			Fortran="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/gfortran.exe"
			CPP="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpp.exe"
			# Flags
			CPPFLAGS="-D__USE_MINGW_ANSI_STDIO=1"
			CFLAGS="-march=pentium4 -mtune=generic -pipe -Wp,-D_FORTIFY_SOURCE=2 -fstack-protector-strong"
			CXXFLAGS="-march=pentium4 -mtune=generic -pipe"
			LDFLAGS="-pipe -Wl,--no-seh -Wl,--large-address-aware"
			RELEASE_FLAGS="-O2 -DNDEBUG"
			DEBUG_FLAGS="-Og -g -ggdb -D_DEBUG"
			MINSIZEREL_FLAGS="-Os -DNDEBUG"
			RELWITHDEBINFO_FLAGS="-O2 -g -ggdb -DNDEBUG"
			# Generation
			MAKEFLAGS="${NPROCS}" #-- Make Flags: change this for DistCC/SMP systems
			MAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/mingw32-make.exe"
			CMAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cmake.exe"
			CPACK="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpack.exe"
			CTEST="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ctest.exe"
			CEDIT="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ccmake.exe"
			NINJA="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ninja.exe"
			GENERATOR="MinGW Makefiles"
			BUILDDIR="${MSYSTEM_PREFIX}"
			;;
		MINGW64)
			# Platform
			CARCH="x86_64"
			CHOST="x86_64-w64-mingw32"
			COMPILER_NAME="GNU"
			COMPILER_VERSION="13.2.0"
			NPROCS="-j$(($(/usr/bin/nproc)+1))"
			# Variables
			MSYSTEM_PREFIX='/mingw64'
			MSYSTEM_CARCH='x86_64'
			MSYSTEM_CHOST='x86_64-w64-mingw32'
			MINGW_CHOST="${MSYSTEM_CHOST}"
			MINGW_PREFIX="${MSYSTEM_PREFIX}"
			MINGW_PACKAGE_PREFIX="mingw-w64-${MSYSTEM_CARCH}"
			# DirectX compatibility environment variable
			DXSDK_DIR=${MSYSTEM_PREFIX}/${MSYSTEM_CHOST}
			if [[ "$DX_MODE" == 1 ]]; then
				BINUTILS_PATH="${DXSDK_DIR}"
			else
				BINUTILS_PATH="${MSYSTEM_PREFIX}"
			fi
			# BinUtils
			AR="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ar.exe"
			AS="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/as.exe"
			LD="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ld.exe"
			NM="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/nm.exe"
			DLLTOOL="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/dlltool.exe"
			RANLIB="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ranlib.exe"
			READELF="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/readelf.exe"
			OBJCOPY="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/objcopy.exe"
			OBJDUMP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/objdump.exe"
			STRIP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/strip.exe"
			# Compilers
			RC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/windres.exe"
			CC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-gcc.exe"
			CXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-g++.exe"
			OBJCC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-gcc.exe"
			OBJCXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-g++.exe"
			Fortran="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/gfortran.exe"
			CPP="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpp.exe"
			# Flags
			CPPFLAGS="-D__USE_MINGW_ANSI_STDIO=1"
			CFLAGS="-march=nocona -msahf -mtune=generic -pipe -Wp,-D_FORTIFY_SOURCE=2 -fstack-protector-strong"
			CXXFLAGS="-march=nocona -msahf -mtune=generic -pipe"
			LDFLAGS="-pipe"
			RELEASE_FLAGS="-O2 -DNDEBUG"
			DEBUG_FLAGS="-Og -g -ggdb -D_DEBUG"
			MINSIZEREL_FLAGS="-Os -DNDEBUG"
			RELWITHDEBINFO_FLAGS="-O2 -g -ggdb -DNDEBUG"
			# Generation
			MAKEFLAGS="${NPROCS}" #-- Make Flags: change this for DistCC/SMP systems
			MAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/mingw32-make.exe"
			CMAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cmake.exe"
			CPACK="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpack.exe"
			CTEST="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ctest.exe"
			CEDIT="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ccmake.exe"
			NINJA="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ninja.exe"
			GENERATOR="MinGW Makefiles"
			BUILDDIR="${MSYSTEM_PREFIX}"
			;;
		CLANG32)
			# Variables
			MSYSTEM_PREFIX='/clang32'
			MSYSTEM_CARCH='i686'
			MSYSTEM_CHOST='i686-w64-mingw32'
			MINGW_CHOST="${MSYSTEM_CHOST}"
			MINGW_PREFIX="${MSYSTEM_PREFIX}"
			MINGW_PACKAGE_PREFIX="mingw-w64-clang-${MSYSTEM_CARCH}"
			export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
			CARCH="i686"
			CHOST="i686-w64-mingw32"
			COMPILER_NAME="CLANG"
			COMPILER_VERSION="16.0.5"
			# Compilers
			CC="clang"
			CXX="clang++"
			# Flags
			CPPFLAGS="-D__USE_MINGW_ANSI_STDIO=1"
			CFLAGS="-march=pentium4 -mtune=generic -O2 -pipe -Wp,-D_FORTIFY_SOURCE=2 -fstack-protector-strong"
			CXXFLAGS="-march=pentium4 -mtune=generic -O2 -pipe"
			LDFLAGS="-pipe -Wl,--no-seh -Wl,--large-address-aware"
			;;
		CLANG64)
			CARCH="x86_64"
			CHOST="x86_64-w64-mingw32"
			COMPILER_NAME="CLANG"
			COMPILER_VERSION="16.0.5"
			NPROCS="-j$(($(/usr/bin/nproc)+1))"
			# Variables
			MSYSTEM_PREFIX='/clang64'
			MSYSTEM_CARCH='x86_64'
			MSYSTEM_CHOST='x86_64-w64-mingw32'
			MINGW_CHOST="${MSYSTEM_CHOST}"
			MINGW_PREFIX="${MSYSTEM_PREFIX}"
			MINGW_PACKAGE_PREFIX="mingw-w64-clang-${MSYSTEM_CARCH}"
			#export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
			# DirectX compatibility environment variable
			# DXSDK_DIR=${MSYSTEM_PREFIX}/${MSYSTEM_CHOST}
			# if [[ "$DX_MODE" == 1 ]]; then
			# 	BINUTILS_PATH="${DXSDK_DIR}"
			# else
			# 	BINUTILS_PATH="${MSYSTEM_PREFIX}"
			# fi
			BINUTILS_PATH="${MSYSTEM_PREFIX}"
			# BinUtils
			AR="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-ar.exe"
			AS="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-as.exe"
			LD="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/lld.exe"
			NM="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-nm.exe"
			DLLTOOL="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-dlltool.exe"
			RANLIB="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-ranlib.exe"
			READELF="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-readelf.exe"
			OBJCOPY="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-objcopy.exe"
			OBJDUMP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-objdump.exe"
			STRIP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/llvm-strip.exe"
			# Compilers
			RC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/windres.exe"
			CC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-clang.exe"
			CXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-clang++.exe"
			OBJCC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-clang.exe"
			OBJCXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-clang++.exe"
			Fortran="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/flang.exe"
			CPP="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpp.exe"
			# Flags
			CPPFLAGS="-D__USE_MINGW_ANSI_STDIO=1"
			CFLAGS="-march=nocona -msahf -mtune=generic -pipe -Wp,-D_FORTIFY_SOURCE=2 -fstack-protector-strong"
			CXXFLAGS="-march=nocona -msahf -mtune=generic -pipe"
			LDFLAGS="-pipe"
			RELEASE_FLAGS="-O2 -DNDEBUG"
			DEBUG_FLAGS="-Og -g -ggdb -D_DEBUG"
			MINSIZEREL_FLAGS="-Os -DNDEBUG"
			RELWITHDEBINFO_FLAGS="-O2 -g -ggdb -DNDEBUG"
			# Generation
			MAKEFLAGS="${NPROCS}" #-- Make Flags: change this for DistCC/SMP systems
			MAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/mingw32-make.exe"
			CMAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cmake.exe"
			CPACK="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpack.exe"
			CTEST="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ctest.exe"
			CEDIT="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ccmake.exe"
			NINJA="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ninja.exe"
			GENERATOR="MinGW Makefiles"
			BUILDDIR="${MSYSTEM_PREFIX}"
			;;
		CLANGARM64)
			# Variables
			MSYSTEM_PREFIX='/clangarm64'
			MSYSTEM_CARCH='aarch64'
			MSYSTEM_CHOST='aarch64-w64-mingw32'
			MINGW_CHOST="${MSYSTEM_CHOST}"
			MINGW_PREFIX="${MSYSTEM_PREFIX}"
			MINGW_PACKAGE_PREFIX="mingw-w64-clang-${MSYSTEM_CARCH}"
			export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
			CARCH="aarch64"
			CHOST="aarch64-w64-mingw32"
			COMPILER_NAME="CLANG"
			COMPILER_VERSION="16.0.5"
			# Compilers
			CC="clang"
			CXX="clang++"
			# Flags
			CPPFLAGS="-D__USE_MINGW_ANSI_STDIO=1"
			CFLAGS="-O2 -pipe -Wp,-D_FORTIFY_SOURCE=2 -fstack-protector-strong"
			CXXFLAGS="-O2 -pipe"
			LDFLAGS="-pipe"
			;;
		UCRT64)
			# Platform
			CARCH="x86_64"
			CHOST="x86_64-w64-mingw32"
			COMPILER_NAME="GNU"
			COMPILER_VERSION="13.2.0"
			NPROCS="-j$(($(/usr/bin/nproc)+1))"
			# Variables
			MSYSTEM_PREFIX='/ucrt64'
			MSYSTEM_CARCH='x86_64'
			MSYSTEM_CHOST='x86_64-w64-mingw32'
			MINGW_CHOST="${MSYSTEM_CHOST}"
			MINGW_PREFIX="${MSYSTEM_PREFIX}"
			MINGW_PACKAGE_PREFIX="mingw-w64-ucrt-${MSYSTEM_CARCH}"
			# DirectX compatibility environment variable
			DXSDK_DIR=${MSYSTEM_PREFIX}/${MSYSTEM_CHOST}
			if [[ "$DX_MODE" == 1 ]]; then
				BINUTILS_PATH="${DXSDK_DIR}"
			else
				BINUTILS_PATH="${MSYSTEM_PREFIX}"
			fi
			# BinUtils
			AR="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ar.exe"
			AS="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/as.exe"
			LD="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ld.exe"
			NM="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/nm.exe"
			DLLTOOL="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/dlltool.exe"
			RANLIB="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ranlib.exe"
			READELF="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/readelf.exe"
			OBJCOPY="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/objcopy.exe"
			OBJDUMP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/objdump.exe"
			STRIP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/strip.exe"
			# Compilers
			RC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/windres.exe"
			CC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-gcc.exe"
			CXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-g++.exe"
			OBJCC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-gcc.exe"
			OBJCXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-g++.exe"
			Fortran="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/gfortran.exe"
			CPP="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpp.exe"
			# Flags
			CPPFLAGS="-D__USE_MINGW_ANSI_STDIO=1"
			CFLAGS="-march=nocona -msahf -mtune=generic -pipe -Wp,-D_FORTIFY_SOURCE=2 -fstack-protector-strong"
			CXXFLAGS="-march=nocona -msahf -mtune=generic -pipe"
			LDFLAGS="-pipe"
			RELEASE_FLAGS="-O2 -DNDEBUG"
			DEBUG_FLAGS="-Og -g -ggdb -D_DEBUG"
			MINSIZEREL_FLAGS="-Os -DNDEBUG"
			RELWITHDEBINFO_FLAGS="-O2 -g -ggdb -DNDEBUG"
			# Generation
			MAKEFLAGS="${NPROCS}" #-- Make Flags: change this for DistCC/SMP systems
			MAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/mingw32-make.exe"
			CMAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cmake.exe"
			CPACK="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpack.exe"
			CTEST="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ctest.exe"
			CEDIT="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ccmake.exe"
			NINJA="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ninja.exe"
			GENERATOR="MinGW Makefiles"
			BUILDDIR="${MSYSTEM_PREFIX}"
			;;
		*)
			MSYSTEM_PREFIX='/usr'
			MSYSTEM_CARCH="$(/usr/bin/uname -m)"
			MSYSTEM_CHOST="${MSYSTEM_CARCH}-pc-msys"
			export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST
			CARCH="$(/usr/bin/uname -m)"
			CHOST="$(/usr/bin/uname -m)-pc-msys"
			COMPILER_NAME="GNU"
			COMPILER_VERSION="11.3.0"
			# DirectX compatibility environment variable
			DXSDK_DIR=${MSYSTEM_PREFIX}/${MSYSTEM_CHOST}
			if [[ "$DX_MODE" == 1 ]]; then
				BINUTILS_PATH="${DXSDK_DIR}"
			else
				BINUTILS_PATH="${MSYSTEM_PREFIX}"
			fi
			# BinUtils
			AR="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ar.exe"
			AS="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/as.exe"
			LD="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ld.exe"
			NM="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/nm.exe"
			DLLTOOL="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/dlltool.exe"
			RANLIB="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/ranlib.exe"
			READELF="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/readelf.exe"
			OBJCOPY="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/objcopy.exe"
			OBJDUMP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/objdump.exe"
			STRIP="${MSYS_INSTALL_PATH}${BINUTILS_PATH}/bin/strip.exe"
			# Compilers
			RC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/windres.exe"
			CC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-gcc.exe"
			CXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-g++.exe"
			OBJCC="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-gcc.exe"
			OBJCXX="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/${MSYSTEM_CHOST}-g++.exe"
			Fortran="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/gfortran.exe"
			CPP="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpp.exe"
			# Flags
			CPPFLAGS=""
			CFLAGS="-march=nocona -msahf -mtune=generic -pipe"
			CXXFLAGS="-march=nocona -msahf -mtune=generic -pipe"
			LDFLAGS="-pipe"
			RELEASE_FLAGS="-O2 -DNDEBUG"
			DEBUG_FLAGS="-Og -g -ggdb -D_DEBUG"
			MINSIZEREL_FLAGS="-Os -DNDEBUG"
			RELWITHDEBINFO_FLAGS="-O2 -g -ggdb -DNDEBUG"
			# Generation
			MAKEFLAGS="${NPROCS}" #-- Make Flags: change this for DistCC/SMP systems
			MAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/make.exe"
			CMAKE="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cmake.exe"
			CPACK="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/cpack.exe"
			CTEST="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ctest.exe"
			CEDIT="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ccmake.exe"
			NINJA="${MSYS_INSTALL_PATH}${MSYSTEM_PREFIX}/bin/ninja.exe"
			GENERATOR="MSYS Makefiles"
			BUILDDIR="${MSYSTEM_PREFIX}"
			;;
	esac

	export \
		CARCH \
		CHOST \
		MSYSTEM_PREFIX \
		MSYSTEM_CARCH \
		MSYSTEM_CHOST \
		DXSDK_DIR \
		RC \
		CC \
		CXX \
		OBJCC \
		OBJCXX \
		Fortran \
		CPP \
		AR \
		AS \
		LD \
		NM \
		DLLTOOL \
		RANLIB \
		READELF \
		OBJCOPY \
		OBJDUMP \
		STRIP \
		RCFLAGS \
		CFLAGS \
		CXXFLAGS \
		OBJCFLAGS \
		OBJCXXFLAGS \
		FortranFLAGS \
		CPPFLAGS \
		LDFLAGS \
		MAKEFLAGS \
		MAKE \
		CMAKE \
		NINJA

	# Custom vars here in case we decide to mute them for some reason...
	export \
		MSYS_INSTALL_PATH \
		COMPILER_NAME \
		COMPILER_VERSION \
		BINUTILS_PATH \
		GENERATOR \
		BUILDDIR


	if [[ "$MSYSTEM" != "MSYS" ]]; then
		export \
			MINGW_CHOST \
			MINGW_PREFIX \
			MINGW_PACKAGE_PREFIX
	fi


	echo ""
	echo "Msys64 Install Path: ${MSYS_INSTALL_PATH}"
	echo ""
	echo "Platform:"
	echo "MSYSTEM: ${MSYSTEM}"
	echo "Msystem Prefix: ${MSYSTEM_PREFIX}"
	echo "C Arch: ${CARCH}"
	echo "C Host: ${CHOST}"
	echo ""
	echo "Compilers:"
	echo "ASM Compiler: ${AS}"
	echo "C Compiler: ${CC}"
	echo "C++ Compiler: ${CXX}"
	echo "RC Compiler: ${RC}"
	echo "Pre-processor: ${CPP}"
	echo "Linker: ${LD}"
	echo ""
	echo "Flags:"
	echo "C Compiler Flags: ${CFLAGS}"
	echo "C++ Compiler Flags: ${CXXFLAGS}"
	echo "RC Compiler Flags: ${RCFLAGS}"
	echo "Pre-processor Flags: ${CPPFLAGS}"
	echo "Linker Flags: ${LDFLAGS}"
	echo ""
	echo "Tools:"
	echo "AR: ${AR}"
	echo "DLLTOOL: ${DLLTOOL}"
	echo "NM: ${NM}"
	echo "OBJCOPY: ${OBJCOPY}"
	echo "OBJDUMP: ${OBJDUMP}"
	echo "RANLIB: ${RANLIB}"
	echo "READELF: ${READELF}"
	echo "STRIP: ${STRIP}"
}


msystem_toolchain_versions ()
{
	echo ""
	echo "Checking RC Compiler..."
	echo ""
	echo "$(${RC} --version)"
	echo ""

	echo ""
	echo "Checking C Compiler..."
	echo ""
	echo "$(${CC} --version)"
	echo ""

	echo ""
	echo "Checking C++ Compiler..."
	echo ""
	echo "$(${CXX} --version)"
	echo ""

	echo ""
	echo "Checking ASM Compiler..."
	echo ""
	echo "$(${AS} --version)"
	echo ""

	echo ""
	echo "Checking Pre-processr..."
	echo ""
	echo "$(${CPP} --version)"
	echo ""

	echo ""
	echo "Checking LD Linker..."
	echo ""
	echo "$(${LD} --version)"
	echo ""

	echo ""
	echo "Checking Make Program..."
	echo ""
	echo "$(${MAKE} --version)"
	echo ""

	echo ""
	echo "Checking CMake Program..."
	echo ""
	echo "$(${CMAKE} --version)"
	echo ""

	echo ""
	echo "Checking Ninja Build..."
	echo ""
	echo "$(${NINJA} --version)"
	echo ""
}

if [[ $1 == "-v" || $1 == "--version" ]]; then
	msystem_toolchain_versions
else
	msystem_toolchain_configure
fi
