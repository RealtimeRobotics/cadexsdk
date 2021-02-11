cmake_minimum_required(VERSION 3.0.2)

set(CadExX3D_LIBRARIES CadEx::X3D)

if(NOT TARGET CadEx::X3D)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExX3D_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExX3D_OWN_INCLUDE_DIRS "${_CadExX3D_install_prefix}/inc/")

    foreach(_dir ${_CadExX3D_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(X3D "${_dir}")
    endforeach()

    set(CadExX3D_INCLUDE_DIRS ${_CadExX3D_OWN_INCLUDE_DIRS})
    set(CadExX3D_DEFINITIONS "")
    set(CadExX3D_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(X3D "Core")

    add_library(CadEx::X3D SHARED IMPORTED)

    set_property(TARGET CadEx::X3D PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExX3D_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(X3D "${_CadExX3D_install_prefix}")

    cadex_check_file_exists(X3D "${CMAKE_CURRENT_LIST_DIR}/CadExX3DConfigVersion.cmake")

endif()
