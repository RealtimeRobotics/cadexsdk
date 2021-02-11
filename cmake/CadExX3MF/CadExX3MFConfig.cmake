cmake_minimum_required(VERSION 3.0.2)

set(CadExX3MF_LIBRARIES CadEx::X3MF)

if (NOT TARGET CadEx::X3MF)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExX3MF_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExX3MF_OWN_INCLUDE_DIRS "${_CadExX3MF_install_prefix}/inc/")

    foreach(_dir ${_CadExX3MF_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(X3MF "${_dir}")
    endforeach()

    set(CadExX3MF_INCLUDE_DIRS ${_CadExX3MF_OWN_INCLUDE_DIRS})
    set(CadExX3MF_DEFINITIONS "")
    set(CadExX3MF_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(X3MF "Core")

    add_library(CadEx::X3MF SHARED IMPORTED)

    set_property(TARGET CadEx::X3MF PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExX3MF_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(X3MF "${_CadExX3MF_install_prefix}")

    cadex_check_file_exists(X3MF "${CMAKE_CURRENT_LIST_DIR}/CadExX3MFConfigVersion.cmake")

endif()