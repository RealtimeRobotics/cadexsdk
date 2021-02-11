cmake_minimum_required(VERSION 3.0.2)

set(CadExDWG_LIBRARIES CadEx::DWG)

if(NOT TARGET CadEx::DWG)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExDWG_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExDWG_OWN_INCLUDE_DIRS "${_CadExDWG_install_prefix}/inc/")

    foreach(_dir ${_CadExDWG_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(DWG "${_dir}")
    endforeach()

    set(CadExDWG_INCLUDE_DIRS ${_CadExDWG_OWN_INCLUDE_DIRS})
    set(CadExDWG_DEFINITIONS "")
    set(CadExDWG_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(DWG "Core")

    add_library(CadEx::DWG SHARED IMPORTED)

    set_property(TARGET CadEx::DWG PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExDWG_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(DWG "${_CadExDWG_install_prefix}")

    cadex_check_file_exists(DWG "${CMAKE_CURRENT_LIST_DIR}/CadExDWGConfigVersion.cmake")

endif()
