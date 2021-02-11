cmake_minimum_required(VERSION 3.0.2)

set(CadExCAT_LIBRARIES CadEx::CAT)

if (NOT TARGET CadEx::CAT)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExCAT_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExCAT_OWN_INCLUDE_DIRS "${_CadExCAT_install_prefix}/inc/")

    foreach(_dir ${_CadExCAT_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(CAT "${_dir}")
    endforeach()

    set(CadExCAT_INCLUDE_DIRS ${_CadExCAT_OWN_INCLUDE_DIRS})
    set(CadExCAT_DEFINITIONS "")
    set(CadExCAT_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(CAT "Core")

    add_library(CadEx::CAT SHARED IMPORTED)

    set_property(TARGET CadEx::CAT PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExCAT_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(CAT "${_CadExCAT_install_prefix}")

    cadex_check_file_exists(CAT "${CMAKE_CURRENT_LIST_DIR}/CadExCATConfigVersion.cmake")
endif()
