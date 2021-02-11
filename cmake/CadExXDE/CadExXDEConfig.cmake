cmake_minimum_required(VERSION 3.0.2)

set(CadExXDE_LIBRARIES CadEx::XDE)

if(NOT TARGET CadEx::XDE)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExXDE_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExXDE_OWN_INCLUDE_DIRS "${_CadExXDE_install_prefix}/inc/")

    foreach(_dir ${_CadExXDE_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(XDE "${_dir}")
    endforeach()

    set(CadExXDE_INCLUDE_DIRS ${_CadExXDE_OWN_INCLUDE_DIRS})
    set(CadExXDE_DEFINITIONS "")
    set(CadExXDE_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(XDE "Core")

    add_library(CadEx::XDE SHARED IMPORTED)

    set_property(TARGET CadEx::XDE PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExXDE_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(XDE "${_CadExXDE_install_prefix}")

    cadex_check_file_exists(XDE "${CMAKE_CURRENT_LIST_DIR}/CadExXDEConfigVersion.cmake")

endif()
