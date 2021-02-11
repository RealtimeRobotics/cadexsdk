cmake_minimum_required(VERSION 3.0.2)

set(CadExMesh_LIBRARIES CadEx::Mesh)

if(NOT TARGET CadEx::Mesh)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExMesh_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExMesh_OWN_INCLUDE_DIRS "${_CadExMesh_install_prefix}/inc/")

    foreach(_dir ${_CadExMesh_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(Mesh "${_dir}")
    endforeach()

    set(CadExMesh_INCLUDE_DIRS ${_CadExMesh_OWN_INCLUDE_DIRS})
    set(CadExMesh_DEFINITIONS "")
    set(CadExMesh_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(Mesh "Core")

    add_library(CadEx::Mesh SHARED IMPORTED)

    set_property(TARGET CadEx::Mesh PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExMesh_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(Mesh "${_CadExMesh_install_prefix}")

    cadex_check_file_exists(Mesh "${CMAKE_CURRENT_LIST_DIR}/CadExMeshConfigVersion.cmake")

endif()
