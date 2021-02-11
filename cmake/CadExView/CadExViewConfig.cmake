cmake_minimum_required(VERSION 3.0.2)

set(CadExView_LIBRARIES CadEx::View)

if(NOT TARGET CadEx::View)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExView_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExView_OWN_INCLUDE_DIRS "${_CadExView_install_prefix}/inc/")

    foreach(_dir ${_CadExView_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(View "${_dir}")
    endforeach()

    set(CadExView_INCLUDE_DIRS ${_CadExView_OWN_INCLUDE_DIRS})
    set(CadExView_DEFINITIONS "")
    set(CadExView_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(View "Core")

    add_library(CadEx::View SHARED IMPORTED)

    set_property(TARGET CadEx::View PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExView_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(View "${_CadExView_install_prefix}")

    cadex_check_file_exists(View "${CMAKE_CURRENT_LIST_DIR}/CadExViewConfigVersion.cmake")

endif()
