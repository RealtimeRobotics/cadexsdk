cmake_minimum_required(VERSION 3.0.2)

set(CadExACIS_LIBRARIES CadEx::ACIS)

if(NOT TARGET CadEx::ACIS)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExACIS_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExACIS_OWN_INCLUDE_DIRS "${_CadExACIS_install_prefix}/inc/")

    foreach(_dir ${_CadExACIS_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(ACIS "${_dir}")
    endforeach()

    set(CadExACIS_INCLUDE_DIRS ${_CadExACIS_OWN_INCLUDE_DIRS})
    set(CadExACIS_DEFINITIONS "")
    set(CadExACIS_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(ACIS "Core")

    add_library(CadEx::ACIS SHARED IMPORTED)

    set_property(TARGET CadEx::ACIS PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExACIS_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(ACIS "${_CadExACIS_install_prefix}")

    cadex_check_file_exists(ACIS "${CMAKE_CURRENT_LIST_DIR}/CadExACISConfigVersion.cmake")

endif()
