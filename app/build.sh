#!/usr/bin/env sh

echo ""
echo "${CMAKE} --build ./out${BUILDDIR}"
echo ""
echo "$(${MAKE} --version)"
echo ""

${CMAKE} --build ./out${BUILDDIR}
