cmake_minimum_required(VERSION 3.0.2)

set(CadExSLD_LIBRARIES CadEx::SLD)

if (NOT TARGET CadEx::SLD)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExSLD_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExSLD_OWN_INCLUDE_DIRS "${_CadExSLD_install_prefix}/inc/")

    foreach(_dir ${_CadExSLD_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(SLD "${_dir}")
    endforeach()

    set(CadExSLD_INCLUDE_DIRS ${_CadExSLD_OWN_INCLUDE_DIRS})
    set(CadExSLD_DEFINITIONS "")
    set(CadExSLD_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(SLD "Core")

    add_library(CadEx::SLD SHARED IMPORTED)

    set_property(TARGET CadEx::SLD PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExSLD_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(SLD "${_CadExSLD_install_prefix}")

    cadex_check_file_exists(SLD "${CMAKE_CURRENT_LIST_DIR}/CadExSLDConfigVersion.cmake")

endif()