#!/usr/bin/env sh

mkdir -p ./out${BUILDDIR}/.cmake/api/v1/query/toolchains-v1

echo ""
echo "$(${CMAKE} --version)"
echo ""

"${CMAKE}" -S "." \
	--no-warn-unused-cli \
	-DCMAKE_ASM_COMPILER:FILEPATH="${AS}" \
	-DCMAKE_CC_COMPILER:FILEPATH="${CC}" \
	-DCMAKE_CXX_COMPILER:FILEPATH="${CXX}" \
	-DCMAKE_OBJC_COMPILER:FILEPATH="${OBJCC}" \
	-DCMAKE_OBJCCXX_COMPILER:FILEPATH="${OBJCXX}" \
	-DCMAKE_Fortran_COMPILER:FILEPATH="${Fortran}" \
	-DCMAKE_RC_COMPILER:FILEPATH="${RC}" \
	-DCMAKE_AR:FILEPATH="${AR}" \
	-DCMAKE_NM:FILEPATH="${NM}" \
	-DCMAKE_LINKER:FILEPATH="${LD}" \
	-DCMAKE_DLLTOOL:FILEPATH="${DLLTOOL}" \
	-DCMAKE_RANLIB:FILEPATH="${RANLIB}" \
	-DCMAKE_READELF:FILEPATH="${READELF}" \
	-DCMAKE_OBJCOPY:FILEPATH="${OBJCOPY}" \
	-DCMAKE_OBJDUMP:FILEPATH="${OBJDUMP}" \
	-DCMAKE_STRIP:FILEPATH="${STRIP}" \
	-DCMAKE_MAKE_PROGRAM:FILEPATH="${MAKE}" \
	-DCMAKE_ASM_FLAGS:FILEPATH="${ASFLAGS}" \
	-DCMAKE_C_FLAGS:FILEPATH="${CFLAGS}" \
	-DCMAKE_CXX_FLAGS:FILEPATH="${CFLAGS}" \
	-DCMAKE_OBJC_FLAGS:FILEPATH="${OBJCFLAGS}" \
	-DCMAKE_OBJCXX_FLAGS:FILEPATH="${OBJCXXFLAGS}" \
	-DCMAKE_Fortran_FLAGS:FILEPATH="${FortranFLAGS}" \
	-DCMAKE_LD_FLAGS:FILEPATH="${LDFLAGS}" \
	-DCMAKE_BUILD_TYPE:STRING=Release \
	-DCMAKE_BUILD_PARALLEL_LEVEL=${NPROCS} \
	-DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
	-B "./out${BUILDDIR}" \
	-G "${GENERATOR}"

if [[ -d "./out${BUILDDIR}/.cmake/api/v1${BUILDDIR}" ]]; then
	rm -rf ./out${BUILDDIR}/.cmake/api/v1${BUILDDIR}
	rm -rf ./out${BUILDDIR}/.cmake/api/v1${BUILDDIR}/CMakeCache.txt
	rm -rf ./out${BUILDDIR}/.cmake/api/v1${BUILDDIR}/compile_commands.json
fi

cp -r \
	./out${BUILDDIR}/.cmake/api/v1/reply \
	./out${BUILDDIR}/.cmake/api/v1${BUILDDIR}

cp \
	./out${BUILDDIR}/CMakeCache.txt \
	./out${BUILDDIR}/.cmake/api/v1${BUILDDIR}/CMakeCache.txt

cp \
	./out${BUILDDIR}/compile_commands.json \
	./out${BUILDDIR}/.cmake/api/v1${BUILDDIR}/compile_commands.json
