cmake_minimum_required(VERSION 3.13.0)
project(cadex_csharp_examples)

cmake_policy(SET CMP0054 NEW)

set(CMAKE_CONFIGURATION_TYPES Debug Release CACHE INTERNAL "" FORCE)

# allow override by cmake argument
if(NOT CADEX_ROOT_DIR)
    set(CADEX_ROOT_DIR "${CMAKE_CURRENT_LIST_DIR}/../..")
endif()

if(NOT CADEX_EXAMPLES_MODELS_DIR)
    set(CADEX_EXAMPLES_MODELS_DIR "${CMAKE_CURRENT_LIST_DIR}/../models")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# license check
if (NOT EXISTS ${CMAKE_CURRENT_LIST_DIR}/cadex_license.cs)
    message (FATAL_ERROR "File '${CMAKE_CURRENT_LIST_DIR}/cadex_license.cs' does not exist. Copy your license key here.")
endif()

option(BUILD_VISUALIZATION_EXAMPLES "Build Visualization examples" ON)

add_subdirectory("advgeom")
add_subdirectory("conversion")
add_subdirectory("exploring")
add_subdirectory("meshing")
add_subdirectory("misc")
add_subdirectory("modeling")
if(BUILD_VISUALIZATION_EXAMPLES)
    add_subdirectory("visualization")
endif()
