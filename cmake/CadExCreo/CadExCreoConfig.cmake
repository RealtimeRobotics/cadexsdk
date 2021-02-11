cmake_minimum_required(VERSION 3.0.2)

set(CadExCreo_LIBRARIES CadEx::Creo)

if (NOT TARGET CadEx::Creo)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExCreo_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExCreo_OWN_INCLUDE_DIRS "${_CadExCreo_install_prefix}/inc/")

    foreach(_dir ${_CadExCreo_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(Creo "${_dir}")
    endforeach()

    set(CadExCreo_INCLUDE_DIRS ${_CadExCreo_OWN_INCLUDE_DIRS})
    set(CadExCreo_DEFINITIONS "")
    set(CadExCreo_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(Creo "Core")

    add_library(CadEx::Creo SHARED IMPORTED)

    set_property(TARGET CadEx::Creo PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExCreo_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(Creo "${_CadExCreo_install_prefix}")

    cadex_check_file_exists(Creo "${CMAKE_CURRENT_LIST_DIR}/CadExCreoConfigVersion.cmake")
endif()
