#------------------------------------------------
# Imber CMake Build System
#------------------------------------------------

cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(ImberEngine
    VERSION 0.0.1
    LANGUAGES CXX
)

set(IMBER_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(IMBER_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(IMBER_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(IMBER_VERSION ${IMBER_VERSION_MAJOR}.${IMBER_VERSION_MINOR}.${IMBER_VERSION_PATCH})
set(IMBER_VERSION_SHORT ${IMBER_VERSION_MAJOR}.${IMBER_VERSION_MINOR})

# use relative paths
set(CMAKE_USE_RELATIVE_PATHS TRUE)
# suppress generation of CHECK_CLEAR target
set(CMAKE_SUPPRESS_REGENERATION TRUE)
# link time optimization
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

#------------------------------------------------
# Directories
#------------------------------------------------

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(IMBER_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})
set(IMBER_SOURCE_DIR ${IMBER_ROOT_DIR}/Source)
set(IMBER_BINARY_DIR ${CMAKE_BINARY_DIR}/Binaries/${CMAKE_SYSTEM_NAME})
set(IMBER_TOOLS_DIR ${IMBER_ROOT_DIR}/Tools)
set(IMBER_THIRD_PARTY_DIR ${IMBER_ROOT_DIR}/ThirdParty)
set(IMBER_SAMPLES_DIR ${IMBER_ROOT_DIR}/Samples)

# Imber cmake scripts dir
list(APPEND CMAKE_MODULE_PATH ${IMBER_TOOLS_DIR}/CMake)

include(GenerateExportHeader)
include(ImberExport)

#------------------------------------------------
# Configurations
#------------------------------------------------

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "" FORCE)

foreach(IMBER_CONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER ${IMBER_CONFIG} UPPER_IMBER_CONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${UPPER_IMBER_CONFIG} ${IMBER_BINARY_DIR}/${IMBER_CONFIG})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${UPPER_IMBER_CONFIG} ${IMBER_BINARY_DIR}/${IMBER_CONFIG})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${UPPER_IMBER_CONFIG} ${IMBER_BINARY_DIR}/${IMBER_CONFIG})
    set(CMAKE_PDB_OUTPUT_DIRECTORY_${UPPER_IMBER_CONFIG} ${IMBER_BINARY_DIR}/${IMBER_CONFIG})
endforeach()

#------------------------------------------------
# Build
#------------------------------------------------

option(IMBER_STATIC "Static build" FALSE)

if (WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ${IMBER_STATIC})
endif()

set(IMBER_LIB STATIC)
if (NOT ${IMBER_STATIC})
    set(IMBER_LIB SHARED)
endif()

# TODO: precompiled headers

#------------------------------------------------
# MSVC configuration
#------------------------------------------------

if (MSVC)
    # TODO: refactor
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>") # or add compile parameter -MTd
    # set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:RelWithDebInfo>:Release>") # or add compile parameter -MT

    # build with multiple processes
    add_compile_options("/MP")
endif()

#------------------------------------------------
# Visual Studio configuration
#------------------------------------------------

if (CMAKE_GENERATOR STREQUAL "Visual Studio 17 2022")
    # TODO: refactor
    # set(CMAKE_VS_EXCLUDE_INTERNAL_FILES OFF)
    # set(CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1)
    # set(CMAKE_VS_INCLUDE_EXTERNAL_FILES ON)

    set(VS_DEBUGGER_WORKING_DIRECTORY ${IMBER_BINARY_DIR})
    # TODO: setup startup project
    # set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Playground)
endif()

add_subdirectory(${IMBER_SOURCE_DIR})
add_subdirectory(${IMBER_SAMPLES_DIR})
# TODO: refactor
# add_subdirectory(${IMBER_TOOLS_DIR})
# add_subdirectory(${IMBER_THIRDPARTY_DIR})

# TODO: build tests var