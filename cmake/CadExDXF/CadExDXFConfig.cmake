cmake_minimum_required(VERSION 3.0.2)

set(CadExDXF_LIBRARIES CadEx::DXF)

if(NOT TARGET CadEx::DXF)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExDXF_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExDXF_OWN_INCLUDE_DIRS "${_CadExDXF_install_prefix}/inc/")

    foreach(_dir ${_CadExDXF_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(DXF "${_dir}")
    endforeach()

    set(CadExDXF_INCLUDE_DIRS ${_CadExDXF_OWN_INCLUDE_DIRS})
    set(CadExDXF_DEFINITIONS "")
    set(CadExDXF_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(DXF "Core")

    add_library(CadEx::DXF SHARED IMPORTED)

    set_property(TARGET CadEx::DXF PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExDXF_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(DXF "${_CadExDXF_install_prefix}")

    cadex_check_file_exists(DXF "${CMAKE_CURRENT_LIST_DIR}/CadExDXFConfigVersion.cmake")

endif()
