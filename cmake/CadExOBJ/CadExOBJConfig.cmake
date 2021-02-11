cmake_minimum_required(VERSION 3.0.2)

set(CadExOBJ_LIBRARIES CadEx::OBJ)

if(NOT TARGET CadEx::OBJ)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExOBJ_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExOBJ_OWN_INCLUDE_DIRS "${_CadExOBJ_install_prefix}/inc/")

    foreach(_dir ${_CadExOBJ_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(OBJ "${_dir}")
    endforeach()

    set(CadExOBJ_INCLUDE_DIRS ${_CadExOBJ_OWN_INCLUDE_DIRS})
    set(CadExOBJ_DEFINITIONS "")
    set(CadExOBJ_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(OBJ "Core")

    add_library(CadEx::OBJ SHARED IMPORTED)

    set_property(TARGET CadEx::OBJ PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExOBJ_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(OBJ "${_CadExOBJ_install_prefix}")

    cadex_check_file_exists(OBJ "${CMAKE_CURRENT_LIST_DIR}/CadExOBJConfigVersion.cmake")

endif()
