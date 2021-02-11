cmake_minimum_required(VERSION 3.0.2)

set(CadExU3D_LIBRARIES CadEx::U3D)

if(NOT TARGET CadEx::U3D)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExU3D_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExU3D_OWN_INCLUDE_DIRS "${_CadExU3D_install_prefix}/inc/")

    foreach(_dir ${_CadExU3D_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(U3D "${_dir}")
    endforeach()

    set(CadExU3D_INCLUDE_DIRS ${_CadExU3D_OWN_INCLUDE_DIRS})
    set(CadExU3D_DEFINITIONS "")
    set(CadExU3D_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(U3D "Core")

    add_library(CadEx::U3D SHARED IMPORTED)

    set_property(TARGET CadEx::U3D PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExU3D_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(U3D "${_CadExU3D_install_prefix}")

    cadex_check_file_exists(U3D "${CMAKE_CURRENT_LIST_DIR}/CadExU3DConfigVersion.cmake")

endif()
