#!/usr/bin/env sh

${CPACK} --config ./out${BUILD_PREFIX}/CPackConfig.cmake

${CPACK} --config ./out${BUILD_PREFIX}/CPackSourceConfig.cmake
