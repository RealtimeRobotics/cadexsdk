cmake_minimum_required(VERSION 3.0.2)

set(CadExCore_LIBRARIES CadEx::Core)

if(NOT TARGET CadEx::Core)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExCore_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExCore_OWN_INCLUDE_DIRS "${_CadExCore_install_prefix}/inc/")

    foreach(_dir ${_CadExCore_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(Core "${_dir}")
    endforeach()

    set(CadExCore_INCLUDE_DIRS ${_CadExCore_OWN_INCLUDE_DIRS})
    set(CadExCore_DEFINITIONS "")
    set(CadExCore_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(Core "")

    add_library(CadEx::Core SHARED IMPORTED)

    set_property(TARGET CadEx::Core PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExCore_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(Core "${_CadExCore_install_prefix}")

    cadex_check_file_exists(Core "${CMAKE_CURRENT_LIST_DIR}/CadExCoreConfigVersion.cmake")

endif()
