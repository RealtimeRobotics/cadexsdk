cmake_minimum_required(VERSION 3.0.2)

set(CadExSTL_LIBRARIES CadEx::STL)

if(NOT TARGET CadEx::STL)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExSTL_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExSTL_OWN_INCLUDE_DIRS "${_CadExSTL_install_prefix}/inc/")

    foreach(_dir ${_CadExSTL_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(STL "${_dir}")
    endforeach()

    set(CadExSTL_INCLUDE_DIRS ${_CadExSTL_OWN_INCLUDE_DIRS})
    set(CadExSTL_DEFINITIONS "")
    set(CadExSTL_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(STL "Core")

    add_library(CadEx::STL SHARED IMPORTED)

    set_property(TARGET CadEx::STL PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExSTL_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(STL "${_CadExSTL_install_prefix}")

    cadex_check_file_exists(STL "${CMAKE_CURRENT_LIST_DIR}/CadExSTLConfigVersion.cmake")

endif()
