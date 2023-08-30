#!/usr/bin/sh

# unset MSYSTEM_PREFIX
# unset MSYSTEM_CARCH
# unset MSYSTEM_CHOST

# unset MINGW_CHOST
# unset MINGW_PREFIX
# unset MINGW_PACKAGE_PREFIX

case "${MSYSTEM}" in
    MINGW32)
        # MSYSTEM_PREFIX='/mingw32'
        # MSYSTEM_CARCH='i686'
        # MSYSTEM_CHOST='i686-w64-mingw32'
        # MINGW_CHOST="${MSYSTEM_CHOST}"
        # MINGW_PREFIX="${MSYSTEM_PREFIX}"
        # MINGW_PACKAGE_PREFIX="mingw-w64-${MSYSTEM_CARCH}"
        # export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
        ;;
    MINGW64)
        # MSYSTEM_PREFIX='/mingw64'
        # MSYSTEM_CARCH='x86_64'
        # MSYSTEM_CHOST='x86_64-w64-mingw32'
        # MINGW_CHOST="${MSYSTEM_CHOST}"
        # MINGW_PREFIX="${MSYSTEM_PREFIX}"
        # MINGW_PACKAGE_PREFIX="mingw-w64-${MSYSTEM_CARCH}"
        # export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
        ;;
    CLANG32)
        # MSYSTEM_PREFIX='/clang32'
        # MSYSTEM_CARCH='i686'
        # MSYSTEM_CHOST='i686-w64-mingw32'
        # MINGW_CHOST="${MSYSTEM_CHOST}"
        # MINGW_PREFIX="${MSYSTEM_PREFIX}"
        # MINGW_PACKAGE_PREFIX="mingw-w64-clang-${MSYSTEM_CARCH}"
        # export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
        ;;
    CLANG64)
        # MSYSTEM_PREFIX='/clang64'
        # MSYSTEM_CARCH='x86_64'
        # MSYSTEM_CHOST='x86_64-w64-mingw32'
        # MINGW_CHOST="${MSYSTEM_CHOST}"
        # MINGW_PREFIX="${MSYSTEM_PREFIX}"
        # MINGW_PACKAGE_PREFIX="mingw-w64-clang-${MSYSTEM_CARCH}"
        # export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
        ;;
    CLANGARM64)
        # MSYSTEM_PREFIX='/clangarm64'
        # MSYSTEM_CARCH='aarch64'
        # MSYSTEM_CHOST='aarch64-w64-mingw32'
        # MINGW_CHOST="${MSYSTEM_CHOST}"
        # MINGW_PREFIX="${MSYSTEM_PREFIX}"
        # MINGW_PACKAGE_PREFIX="mingw-w64-clang-${MSYSTEM_CARCH}"
        # export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
        ;;
    UCRT64)
		## System
		CARCH="x86_64"
		CHOST="x86_64-w64-mingw32"
		# MSYSTEM_PREFIX='/ucrt64'
        # MSYSTEM_CARCH='x86_64'
        # MSYSTEM_CHOST='x86_64-w64-mingw32'
        # MINGW_CHOST="${MSYSTEM_CHOST}"
        # MINGW_PREFIX="${MSYSTEM_PREFIX}"
        # MINGW_PACKAGE_PREFIX="mingw-w64-ucrt-${MSYSTEM_CARCH}"
		## Toolchain
		CC="${MSYSTEM_PREFIX}/bin/x86_64-w64-mingw32-gcc.exe"
		CXX="${MSYSTEM_PREFIX}/bin/x86_64-w64-mingw32-g++.exe"
		RC="${MSYSTEM_PREFIX}/bin/windres.exe"
		## Bin utils
		AR="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/ar.exe"
		AS="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/as.exe"
		DLLTOOL="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/dlltool.exe"
		LD="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/ld.exe"
		NM="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/nm.exe"
		OBJCOPY="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/objcopy.exe"
		OBJDUMP="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/objdump.exe"
		RANLIB="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/ranlib.exe"
		READELF="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/readelf.exe"
		STRIP="${MSYSTEM_PREFIX}/x86_64-w64-mingw32/bin/strip.exe"
		## Make
		MAKE="${MSYSTEM_PREFIX}/bin/mingw32-make.exe"
		## Flags
		CPPFLAGS="-D__USE_MINGW_ANSI_STDIO=1"
		CFLAGS="-march=nocona -msahf -mtune=generic -O2 -pipe -Wp,-D_FORTIFY_SOURCE=2 -fstack-protector-strong"
		CXXFLAGS="-march=nocona -msahf -mtune=generic -O2 -pipe"
		LDFLAGS="-pipe -ld2d1 -lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32"
		export CARCH CHOST CC CXX LD RC AR NM RANLIB MAKE CPPFLAGS CFLAGS CXXFLAGS LDFLAGS
        # export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST MINGW_CHOST MINGW_PREFIX MINGW_PACKAGE_PREFIX
        ;;
    *)
        # MSYSTEM_PREFIX='/usr'
        # MSYSTEM_CARCH="$(/usr/bin/uname -m)"
        # MSYSTEM_CHOST="${MSYSTEM_CARCH}-pc-msys"
        # export MSYSTEM_PREFIX MSYSTEM_CARCH MSYSTEM_CHOST
        ;;
esac

# DirectX compatibility environment variable
DXSDK_DIR=${MINGW_PREFIX}/${MINGW_CHOST}

#-- Make Flags: change this for DistCC/SMP systems
MAKEFLAGS="-j$(($(nproc)+1))"
#-- Debugging flags
DEBUG_CFLAGS="-ggdb -Og"
DEBUG_CXXFLAGS="-ggdb -Og"

ACLOCAL_PATH="${MINGW_PREFIX}/share/aclocal:/usr/share/aclocal"
PKG_CONFIG_PATH="${MINGW_PREFIX}/lib/pkgconfig:${MINGW_PREFIX}/share/pkgconfig"

#########################################################################
# BUILD ENVIRONMENT
#########################################################################
#
# Makepkg defaults: BUILDENV=(!distcc !color !ccache check !sign)
#  A negated environment option will do the opposite of the comments below.
#
#-- distcc:   Use the Distributed C/C++/ObjC compiler
#-- color:    Colorize output messages
#-- ccache:   Use ccache to cache compilation
#-- check:    Run the check() function if present in the PKGBUILD
#-- sign:     Generate PGP signature file
#
BUILDENV=(!distcc color !ccache check !sign)
#
#-- If using DistCC, your MAKEFLAGS will also need modification. In addition,
#-- specify a space-delimited list of hosts running in the DistCC cluster.
#DISTCC_HOSTS=""
#
#-- Specify a directory for package building.
#BUILDDIR=/tmp/makepkg

#########################################################################
# GLOBAL PACKAGE OPTIONS
#   These are default values for the options=() settings
#########################################################################
#
# Makepkg defaults: OPTIONS=(!strip docs libtool staticlibs emptydirs !zipman !purge !debug !lto)
#  A negated option will do the opposite of the comments below.
#
#-- strip:      Strip symbols from binaries/libraries
#-- docs:       Save doc directories specified by DOC_DIRS
#-- libtool:    Leave libtool (.la) files in packages
#-- staticlibs: Leave static library (.a) files in packages
#-- emptydirs:  Leave empty directories in packages
#-- zipman:     Compress manual (man and info) pages in MAN_DIRS with gzip
#-- purge:      Remove files specified by PURGE_TARGETS
#-- debug:      Add debugging flags as specified in DEBUG_* variables
#-- lto:        Add compile flags for building with link time optimization
#
OPTIONS=(strip docs !libtool staticlibs emptydirs zipman purge !debug !lto)

#-- File integrity checks to use. Valid: md5, sha1, sha256, sha384, sha512
INTEGRITY_CHECK=(sha256)
#-- Options to be used when stripping binaries. See `man strip' for details.
STRIP_BINARIES="--strip-all"
#-- Options to be used when stripping shared libraries. See `man strip' for details.
STRIP_SHARED="--strip-unneeded"
#-- Options to be used when stripping static libraries. See `man strip' for details.
STRIP_STATIC="--strip-debug"
#-- Manual (man and info) directories to compress (if zipman is specified)
MAN_DIRS=("${MINGW_PREFIX#/}"{{,/local}{,/share},/opt/*}/{man,info})
#-- Doc directories to remove (if !docs is specified)
DOC_DIRS=("${MINGW_PREFIX#/}"/{,local/}{,share/}{doc,gtk-doc})
#-- Files to be removed from all packages (if purge is specified)
PURGE_TARGETS=("${MINGW_PREFIX#/}"/{,share}/info/dir .packlist *.pod)

#########################################################################
# PACKAGE OUTPUT
#########################################################################
#
# Default: put built package and cached source in build directory
#
#-- Destination: specify a fixed directory where all packages will be placed
#PKGDEST=/var/packages-mingw64
#-- Source cache: specify a fixed directory where source files will be cached
#SRCDEST=/var/sources
#-- Source packages: specify a fixed directory where all src packages will be placed
#SRCPKGDEST=/var/srcpackages-mingw64
#-- Log files: specify a fixed directory where all log files will be placed
#LOGDEST=/var/makepkglogs
#-- Packager: name/email of the person or organization building packages
#PACKAGER="John Doe <john@doe.com>"
#-- Specify a key to use for package signing
#GPGKEY=""

#########################################################################
# COMPRESSION DEFAULTS
#########################################################################
#
COMPRESSGZ=(gzip -c -f -n)
COMPRESSBZ2=(bzip2 -c -f)
COMPRESSXZ=(xz -c -z -T0 -)
COMPRESSZST=(zstd -c -T0 --ultra -20 -)
COMPRESSLRZ=(lrzip -q)
COMPRESSLZO=(lzop -q)
COMPRESSZ=(compress -c -f)
COMPRESSLZ4=(lz4 -q)
COMPRESSLZ=(lzip -c -f)

#########################################################################
# EXTENSION DEFAULTS
#########################################################################
#
PKGEXT='.pkg.tar.zst'
SRCEXT='.src.tar.zst'

#########################################################################
# OTHER
#########################################################################
#
#-- Command used to run pacman as root, instead of trying sudo and su
PACMAN_AUTH=()
