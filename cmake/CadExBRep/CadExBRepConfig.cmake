cmake_minimum_required(VERSION 3.0.2)

set(CadExBRep_LIBRARIES CadEx::BRep)

if(NOT TARGET CadEx::BRep)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExBRep_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExBRep_OWN_INCLUDE_DIRS "${_CadExBRep_install_prefix}/inc/")

    foreach(_dir ${_CadExBRep_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(BRep "${_dir}")
    endforeach()

    set(CadExBRep_INCLUDE_DIRS ${_CadExBRep_OWN_INCLUDE_DIRS})
    set(CadExBRep_DEFINITIONS "")
    set(CadExBRep_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(BRep "Core")

    add_library(CadEx::BRep SHARED IMPORTED)

    set_property(TARGET CadEx::BRep PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExBRep_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(BRep "${_CadExBRep_install_prefix}")

    cadex_check_file_exists(BRep "${CMAKE_CURRENT_LIST_DIR}/CadExBRepConfigVersion.cmake")

endif()
