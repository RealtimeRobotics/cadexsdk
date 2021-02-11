cmake_minimum_required(VERSION 3.0.2)

set(CadExX3DPDF_LIBRARIES CadEx::X3DPDF)

if (NOT TARGET CadEx::X3DPDF)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExX3DPDF_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExX3DPDF_OWN_INCLUDE_DIRS "${_CadExX3DPDF_install_prefix}/inc/")

    foreach(_dir ${_CadExX3DPDF_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(X3DPDF "${_dir}")
    endforeach()

    set(CadExX3DPDF_INCLUDE_DIRS ${_CadExX3DPDF_OWN_INCLUDE_DIRS})
    set(CadExX3DPDF_DEFINITIONS "")
    set(CadExX3DPDF_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(X3DPDF "Core")

    add_library(CadEx::X3DPDF SHARED IMPORTED)

    set_property(TARGET CadEx::X3DPDF PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExX3DPDF_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(X3DPDF "${_CadExX3DPDF_install_prefix}")

    cadex_check_file_exists(X3DPDF "${CMAKE_CURRENT_LIST_DIR}/CadExX3DPDFConfigVersion.cmake")

endif()
