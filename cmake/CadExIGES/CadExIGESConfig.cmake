cmake_minimum_required(VERSION 3.0.2)

set(CadExIGES_LIBRARIES CadEx::IGES)

if(NOT TARGET CadEx::IGES)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExIGES_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExIGES_OWN_INCLUDE_DIRS "${_CadExIGES_install_prefix}/inc/")

    foreach(_dir ${_CadExIGES_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(IGES "${_dir}")
    endforeach()

    set(CadExIGES_INCLUDE_DIRS ${_CadExIGES_OWN_INCLUDE_DIRS})
    set(CadExIGES_DEFINITIONS "")
    set(CadExIGES_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(IGES "Core")

    add_library(CadEx::IGES SHARED IMPORTED)

    set_property(TARGET CadEx::IGES PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExIGES_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(IGES "${_CadExIGES_install_prefix}")

    cadex_check_file_exists(IGES "${CMAKE_CURRENT_LIST_DIR}/CadExIGESConfigVersion.cmake")

endif()
