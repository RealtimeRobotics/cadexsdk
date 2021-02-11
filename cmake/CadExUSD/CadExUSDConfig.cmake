cmake_minimum_required(VERSION 3.0.2)

set(CadExUSD_LIBRARIES CadEx::USD)

if(NOT TARGET CadEx::USD)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExUSD_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExUSD_OWN_INCLUDE_DIRS "${_CadExUSD_install_prefix}/inc/")

    foreach(_dir ${_CadExUSD_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(USD "${_dir}")
    endforeach()

    set(CadExUSD_INCLUDE_DIRS ${_CadExUSD_OWN_INCLUDE_DIRS})
    set(CadExUSD_DEFINITIONS "")
    set(CadExUSD_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(USD "Core")

    add_library(CadEx::USD SHARED IMPORTED)

    set_property(TARGET CadEx::USD PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExUSD_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(USD "${_CadExUSD_install_prefix}")

    cadex_check_file_exists(USD "${CMAKE_CURRENT_LIST_DIR}/CadExUSDConfigVersion.cmake")

endif()
