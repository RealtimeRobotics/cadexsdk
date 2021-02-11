cmake_minimum_required(VERSION 3.13)
project(cadex_cxx_examples)

cmake_policy(SET CMP0054 NEW)

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE INTERNAL "" FORCE)

# allow override by cmake argument
if(NOT CADEX_ROOT_DIR)
    set(CADEX_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
endif()

if(NOT CADEX_EXAMPLES_MODELS_DIR)
    set(CADEX_EXAMPLES_MODELS_DIR "${CMAKE_CURRENT_LIST_DIR}/../models")
endif()

# Add path to CAD Exchanger cmake config files.
list(APPEND CMAKE_PREFIX_PATH "${CADEX_ROOT_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
endif()

# license check
if (NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/cadex_license.cxx)
    message (WARNING "File '${CMAKE_CURRENT_LIST_DIR}/cadex_license.cxx' does not exist. Copy your license key here.")
endif()

set(BUILD_VISUALIZATION_EXAMPLES ON CACHE BOOL "Build Visualization examples")

if (NOT QT_ROOT_DIR)
    set(QT_ROOT_DIR $ENV{QT_ROOT_DIR})
endif()
if (QT_ROOT_DIR)
    set(Qt5_DIR "${QT_ROOT_DIR}/lib/cmake/Qt5")
endif()
# Qt Creator set CMAKE_PREFIX_PATH variable to path to Qt lib installation.
find_package(Qt5 COMPONENTS Core QUIET)
if (Qt5_FOUND)
    if (Qt5Core_VERSION VERSION_GREATER_EQUAL 5.12)
        set(BUILD_QT_EXAMPLES ON)
    else()
        message(STATUS "Skipping progressindicator and Qt5 visualization cxx examples.\nMinimum required Qt version is 5.12")
    endif()
else()
    # make available QT_ROOT_DIR for cmake-gui
    set(QT_ROOT_DIR "" CACHE PATH "Path to Qt 5 installed" FORCE)
    message (STATUS "Skipping progressindicator and Qt5 visualization cxx examples.\nUnable find Qt root. Neither cmake variable \"QT_ROOT_DIR\" nor environment variable \"QT_ROOT_DIR\" is defined.")
endif()


add_subdirectory("advgeom")
add_subdirectory("conversion")
add_subdirectory("exploring")
add_subdirectory("meshing")
add_subdirectory("modeling")
add_subdirectory("misc")
if (BUILD_VISUALIZATION_EXAMPLES)
  add_subdirectory("visualization")
endif()
