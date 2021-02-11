cmake_minimum_required(VERSION 3.0.2)

set(CadExSTEP_LIBRARIES CadEx::STEP)

if(NOT TARGET CadEx::STEP)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExSTEP_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExSTEP_OWN_INCLUDE_DIRS "${_CadExSTEP_install_prefix}/inc/")

    foreach(_dir ${_CadExSTEP_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(STEP "${_dir}")
    endforeach()

    set(CadExSTEP_INCLUDE_DIRS ${_CadExSTEP_OWN_INCLUDE_DIRS})
    set(CadExSTEP_DEFINITIONS "")
    set(CadExSTEP_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(STEP "Core")

    add_library(CadEx::STEP SHARED IMPORTED)

    set_property(TARGET CadEx::STEP PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExSTEP_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(STEP "${_CadExSTEP_install_prefix}")

    cadex_check_file_exists(STEP "${CMAKE_CURRENT_LIST_DIR}/CadExSTEPConfigVersion.cmake")

endif()
