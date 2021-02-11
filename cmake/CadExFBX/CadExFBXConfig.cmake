cmake_minimum_required(VERSION 3.0.2)

set(CadExFBX_LIBRARIES CadEx::FBX)

if (NOT TARGET CadEx::FBX)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExFBX_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExFBX_OWN_INCLUDE_DIRS "${_CadExFBX_install_prefix}/inc/")

    foreach(_dir ${_CadExFBX_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(FBX "${_dir}")
    endforeach()

    set(CadExFBX_INCLUDE_DIRS ${_CadExFBX_OWN_INCLUDE_DIRS})
    set(CadExFBX_DEFINITIONS "")
    set(CadExFBX_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(FBX "Core")

    add_library(CadEx::FBX SHARED IMPORTED)

    set_property(TARGET CadEx::FBX PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExFBX_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(FBX "${_CadExFBX_install_prefix}")

    cadex_check_file_exists(FBX "${CMAKE_CURRENT_LIST_DIR}/CadExFBXConfigVersion.cmake")

endif()