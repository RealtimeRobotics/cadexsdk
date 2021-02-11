cmake_minimum_required(VERSION 3.0.2)

set(CadExVRML_LIBRARIES CadEx::VRML)

if(NOT TARGET CadEx::VRML)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExVRML_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExVRML_OWN_INCLUDE_DIRS "${_CadExVRML_install_prefix}/inc/")

    foreach(_dir ${_CadExVRML_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(VRML "${_dir}")
    endforeach()

    set(CadExVRML_INCLUDE_DIRS ${_CadExVRML_OWN_INCLUDE_DIRS})
    set(CadExVRML_DEFINITIONS "")
    set(CadExVRML_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(VRML "Core")

    add_library(CadEx::VRML SHARED IMPORTED)

    set_property(TARGET CadEx::VRML PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExVRML_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(VRML "${_CadExVRML_install_prefix}")

    cadex_check_file_exists(VRML "${CMAKE_CURRENT_LIST_DIR}/CadExVRMLConfigVersion.cmake")

endif()
