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

set(${PROJECT_NAME}_REQUIRED_DEFS)
list(APPEND ${PROJECT_NAME}_REQUIRED_DEFS
	UNICODE
	_UNICODE
)

set(${PROJECT_NAME}_REQUIRED_FLAGS)
if(NOT (CYGWIN OR MSYS))
	list(APPEND ${PROJECT_NAME}_REQUIRED_FLAGS -municode)
endif()

list(APPEND ${PROJECT_NAME}_REQUIRED_FLAGS -mwindows)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/Main.h" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}")
file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/MainComponent.h" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}")

add_library (window)
add_library (${PROJECT_NAME}::window ALIAS window)

target_include_directories (window

    PRIVATE

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources (window

    PRIVATE

        FILE_SET window_PRIVATE_HEADERS
        TYPE HEADERS

        BASE_DIRS
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        FILES
            # include/${PROJECT_NAME}/MainComponent.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/MainComponent.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/MainComponent.h>
)

target_sources (window

    PRIVATE
        # src/runtime/main.cpp
        "${CMAKE_CURRENT_SOURCE_DIR}/src/MainComponent.cpp"
)

set_target_properties (window

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin
)

target_compile_definitions (window

	PUBLIC
		${${PROJECT_NAME}_REQUIRED_DEFS}
)

target_compile_options (window

	PUBLIC
		${${PROJECT_NAME}_REQUIRED_FLAGS}
)
target_link_options (window

	PUBLIC
		${${PROJECT_NAME}_REQUIRED_FLAGS}
)

add_executable (executable)
add_executable (${PROJECT_NAME}::executable ALIAS executable)

target_include_directories (executable

    PRIVATE

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties (executable

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin
)

target_sources (executable

    PRIVATE

        FILE_SET executable_PRIVATE_HEADERS
        TYPE HEADERS

        BASE_DIRS
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        FILES
            # include/${PROJECT_NAME}/main.h
            $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/Main.h>
            $<INSTALL_INTERFACE:include/${PROJECT_NAME}/Main.h>
)

target_sources (executable

    PRIVATE
        # src/runtime/main.cpp
        "${CMAKE_CURRENT_SOURCE_DIR}/src/Main.cpp"
)

set_target_properties (executable

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin
)

target_compile_definitions(executable

	PUBLIC
		${${PROJECT_NAME}_REQUIRED_DEFS}
)

target_compile_options(executable

	PUBLIC
		${${PROJECT_NAME}_REQUIRED_FLAGS}
)

target_link_options (executable

	PUBLIC
		${${PROJECT_NAME}_REQUIRED_FLAGS}
)

target_link_libraries (executable

    ${PROJECT_NAME}::window
)



install(
	TARGETS window executable
	EXPORT CxxWinTargets
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install (
	EXPORT CxxWinTargets
	FILE CxxWinTargets.cmake
	NAMESPACE ${PROJECT_NAME}::
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

# ##-- Create package config
include (CMakePackageConfigHelpers)

configure_package_config_file (
	"${CMAKE_CURRENT_SOURCE_DIR}/share/CxxWinConfig.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/CxxWinConfig.cmake"
	INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

install (
	FILES
	"${CMAKE_CURRENT_BINARY_DIR}/CxxWinConfig.cmake"
	DESTINATION
	"${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

export(
	EXPORT CxxWinTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/CxxWinTargets.cmake"
	NAMESPACE ${PROJECT_NAME}::
)
