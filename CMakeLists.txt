cmake_minimum_required (VERSION 3.14...3.27 FATAL_ERROR)

list (APPEND CMAKE_MODULE_PATH
	"${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules"
)

project (CxxWin)
enable_language (CXX)

include(GNUInstallDirs)

set (PROJECT_VERSION_MAJOR 1)
set (PROJECT_VERSION_MINOR 0)
set (PROJECT_VERSION_PATCH 0)

include (GetSourceInfo)
get_source_info ()
set (PROJECT_VERSION_TWEAK "${git_revision}")
# set(PROJECT_VERSION_TWEAK "x")

set (${PROJECT_NAME}_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${PROJECT_VERSION_TWEAK}" CACHE STRING "Value given to the ``VERSION`` option of the most recent call to the ``project()`` command, if any." FORCE)
set (${PROJECT_NAME}_DESCRIPTION "A quick one-and-done Win32 API project implementing a COM blank application window for Windows platforms in C++." CACHE STRING "Short project description given to the project command." FORCE)
set (${PROJECT_NAME}_HOMEPAGE_URL "https://github.com/StoneyDSP/CxxWin.git" CACHE STRING "The homepage URL of the project." FORCE)

option (OPTION_SHARED_LIBS "Global flag to cause ``add_library()`` to create shared libraries if on." ON)

if (OPTION_SHARED_LIBS)
	set (BUILD_SHARED_LIBS ON CACHE BOOL "Global flag to cause ``add_library()`` to create shared libraries if on." FORCE)
else ()
	set (BUILD_SHARED_LIBS OFF CACHE BOOL "Global flag to cause ``add_library()`` to create shared libraries if on." FORCE)
endif ()

set(CMAKE_CXX_FLAGS "-DUNICODE -D_UNICODE -std=c++17 -ld2d1 -lcomctl32 -Wl,--subsystem,windows" CACHE
STRING "" FORCE)

file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/win32_core.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/win32_core.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/win32_core.mm"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core"
)

file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/native/win32_BasicNativeHeaders.h"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/native"
)

file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/window/win32_BaseWindow.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/window/win32_DPIScale.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/window/win32_MainWindow.h"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/window"
)

file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system/win32_CompilerSupport.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system/win32_PlatformDefs.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system/win32_StandardHeader.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system/win32_TargetPlatform.h"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system"
)

file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/modules/Win32_core/memory/win32_SmartPointer.h"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/memory"
)

add_library (library)
add_library (${PROJECT_NAME}::library ALIAS library)

target_include_directories (library

    PRIVATE

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources (library

    PUBLIC

        FILE_SET library_HEADERS
        TYPE HEADERS

        BASE_DIRS
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        FILES
            # include/${PROJECT_NAME}/modules/Win32_core/system/win32_CompilerSupport.h"
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system/win32_CompilerSupport.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/system/win32_CompilerSupport.h>

            # include/${PROJECT_NAME}/modules/Win32_core/system/win32_PlatformDefs.h"
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system/win32_PlatformDefs.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/system/win32_PlatformDefs.h>

            # include/${PROJECT_NAME}/modules/Win32_core/native/win32_BasicNativeHeaders.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/native/win32_BasicNativeHeaders.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/native/win32_BasicNativeHeaders.h>

            # include/${PROJECT_NAME}/modules/Win32_core/system/win32_TargetPlatform.h"
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system/win32_TargetPlatform.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/system/win32_TargetPlatform.h>

            # include/${PROJECT_NAME}/modules/Win32_core/system/win32_StandardHeader.h"
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/system/win32_StandardHeader.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/system/win32_StandardHeader.h>

            # include/${PROJECT_NAME}/modules/Win32_core/win32_core.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/win32_core.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/win32_core.h>

            # include/${PROJECT_NAME}/modules/Win32_core/window/win32_DPIScale.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/window/win32_DPIScale.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/window/win32_DPIScale.h>

            # include/${PROJECT_NAME}/modules/Win32_core/window/win32_BaseWindow.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/window/win32_BaseWindow.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/window/win32_BaseWindow.h>

            # include/${PROJECT_NAME}/modules/Win32_core/window/win32_MainWindow.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/modules/Win32_core/window/win32_MainWindow.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/modules/Win32_core/window/win32_MainWindow.h>
)

target_sources (library

    PRIVATE
        # "include/${PROJECT_NAME}/modules/Win32_core/win32_core.mm"
        "include/${PROJECT_NAME}/modules/Win32_core/win32_core.cpp"
)

set_target_properties (library

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin
)

target_compile_definitions (library

	PUBLIC
        UNICODE
        _UNICODE
)

target_compile_features (library
    PUBLIC
        cxx_std_17
)

target_compile_options (library

	PUBLIC
        -municode -mwindows -Wl,--subsystem,windows
)

target_link_libraries (library

    PUBLIC
        d2d1
        comctl32
)

# target_sources (modules

#     PRIVATE
#         "include/${PROJECT_NAME}/modules/Win32_core/win32_core.mm"
#         # "include/${PROJECT_NAME}/modules/Win32_core/win32_core.cpp"
#         # "include/${PROJECT_NAME}/modules/Win32_core/window/win32_MainWindow.cpp"
#         # "include/${PROJECT_NAME}/modules/Win32_core/window/win32_BaseWindow.cpp"
# )

file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/Main.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}/MainComponent.h"
    DESTINATION
    "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}"
)

add_executable (executable)
add_executable (${PROJECT_NAME}::executable ALIAS executable)

target_include_directories (executable

    PRIVATE

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources (executable

    PUBLIC

        FILE_SET executable_HEADERS
        TYPE HEADERS

        BASE_DIRS
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        FILES
            # include/${PROJECT_NAME}/MainComponent.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/MainComponent.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/MainComponent.h>

            # include/${PROJECT_NAME}/main.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Main.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Main.h>
)

target_sources (executable

    PRIVATE
        "include/${PROJECT_NAME}/MainComponent.cpp"
        "include/${PROJECT_NAME}/Main.cpp"
)

set_target_properties (executable

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin
)

target_compile_definitions (executable

	PUBLIC
        UNICODE
        _UNICODE
)

target_compile_features (executable
    PUBLIC
        cxx_std_17
)

target_compile_options (executable

	PUBLIC
        -municode -mwindows -Wl,--subsystem,windows
)

target_link_libraries (executable

    PUBLIC
        ${PROJECT_NAME}::library
        d2d1
        comctl32
)

# Create targets to export
install(
	TARGETS library executable
	EXPORT CxxWinTargets
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILE_SET library_HEADERS
    FILE_SET executable_HEADERS
)

install (
	EXPORT CxxWinTargets
	FILE CxxWinTargets.cmake
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# Export targets to binary dir
export(
	EXPORT CxxWinTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/CxxWinTargets.cmake"
	NAMESPACE ${PROJECT_NAME}::
)

# ##-- Create CMake package config
include (CMakePackageConfigHelpers)

configure_package_config_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/share/CxxWinConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/CxxWinConfig.cmake"
	INSTALL_DESTINATION
    "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install (
	FILES
	    "${CMAKE_CURRENT_BINARY_DIR}/CxxWinConfig.cmake"
	DESTINATION
	    "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)
