cmake_minimum_required(VERSION 3.0.2)

set(CadExCollada_LIBRARIES CadEx::Collada)

if (NOT TARGET CadEx::Collada)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExCollada_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExCollada_OWN_INCLUDE_DIRS "${_CadExCollada_install_prefix}/inc/")

    foreach(_dir ${_CadExCollada_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(Collada "${_dir}")
    endforeach()

    set(CadExCollada_INCLUDE_DIRS ${_CadExCollada_OWN_INCLUDE_DIRS})
    set(CadExCollada_DEFINITIONS "")
    set(CadExCollada_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(Collada "Core")

    add_library(CadEx::Collada SHARED IMPORTED)

    set_property(TARGET CadEx::Collada PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExCollada_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(Collada "${_CadExCollada_install_prefix}")

    cadex_check_file_exists(Collada "${CMAKE_CURRENT_LIST_DIR}/CadExColladaConfigVersion.cmake")
endif()
