cmake_minimum_required(VERSION 3.0.2)

set(CadExJT_LIBRARIES CadEx::JT)

if(NOT TARGET CadEx::JT)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExJT_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExJT_OWN_INCLUDE_DIRS "${_CadExJT_install_prefix}/inc/")

    foreach(_dir ${_CadExJT_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(JT "${_dir}")
    endforeach()

    set(CadExJT_INCLUDE_DIRS ${_CadExJT_OWN_INCLUDE_DIRS})
    set(CadExJT_DEFINITIONS "")
    set(CadExJT_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(JT "Core;Para")

    add_library(CadEx::JT SHARED IMPORTED)

    set_property(TARGET CadEx::JT PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExJT_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(JT "${_CadExJT_install_prefix}")

    cadex_check_file_exists(JT "${CMAKE_CURRENT_LIST_DIR}/CadExJTConfigVersion.cmake")

endif()
