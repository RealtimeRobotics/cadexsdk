cmake_minimum_required(VERSION 3.0.2)

set(CadExNX_LIBRARIES CadEx::NX)

if (NOT TARGET CadEx::NX)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExNX_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExNX_OWN_INCLUDE_DIRS "${_CadExNX_install_prefix}/inc/")

    foreach(_dir ${_CadExNX_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(NX "${_dir}")
    endforeach()

    set(CadExNX_INCLUDE_DIRS ${_CadExNX_OWN_INCLUDE_DIRS})
    set(CadExNX_DEFINITIONS "")
    set(CadExNX_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(NX "Core;JT;Para")

    add_library(CadEx::NX SHARED IMPORTED)

    set_property(TARGET CadEx::NX PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExNX_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(NX "${_CadExNX_install_prefix}")

    cadex_check_file_exists(NX "${CMAKE_CURRENT_LIST_DIR}/CadExNXConfigVersion.cmake")
endif()
