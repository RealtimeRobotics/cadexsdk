cmake_minimum_required(VERSION 3.0.2)

set(CadExAdvGeom_LIBRARIES CadEx::AdvGeom)

if(NOT TARGET CadEx::AdvGeom)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExAdvGeom_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExAdvGeom_OWN_INCLUDE_DIRS "${_CadExAdvGeom_install_prefix}/inc/")

    foreach(_dir ${_CadExAdvGeom_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(AdvGeom "${_dir}")
    endforeach()

    set(CadExAdvGeom_INCLUDE_DIRS ${_CadExAdvGeom_OWN_INCLUDE_DIRS})
    set(CadExAdvGeom_DEFINITIONS "")
    set(CadExAdvGeom_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(AdvGeom "Core")

    add_library(CadEx::AdvGeom SHARED IMPORTED)

    set_property(TARGET CadEx::AdvGeom PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExAdvGeom_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(AdvGeom "${_CadExAdvGeom_install_prefix}")

    cadex_check_file_exists(AdvGeom "${CMAKE_CURRENT_LIST_DIR}/CadExAdvGeomConfigVersion.cmake")

endif()
