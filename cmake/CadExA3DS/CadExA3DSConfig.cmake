cmake_minimum_required(VERSION 3.0.2)

set(CadExA3DS_LIBRARIES CadEx::A3DS)

if(NOT TARGET CadEx::A3DS)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExA3DS_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExA3DS_OWN_INCLUDE_DIRS "${_CadExA3DS_install_prefix}/inc/")

    foreach(_dir ${_CadExA3DS_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(A3DS "${_dir}")
    endforeach()

    set(CadExA3DS_INCLUDE_DIRS ${_CadExA3DS_OWN_INCLUDE_DIRS})
    set(CadExA3DS_DEFINITIONS "")
    set(CadExA3DS_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(A3DS "Core")

    add_library(CadEx::A3DS SHARED IMPORTED)

    set_property(TARGET CadEx::A3DS PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExA3DS_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(A3DS "${_CadExA3DS_install_prefix}")

    cadex_check_file_exists(A3DS "${CMAKE_CURRENT_LIST_DIR}/CadExA3DSConfigVersion.cmake")

endif()
