cmake_minimum_required(VERSION 3.0.2)

set(CadExGLTF_LIBRARIES CadEx::GLTF)

if (NOT TARGET CadEx::GLTF)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExGLTF_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExGLTF_OWN_INCLUDE_DIRS "${_CadExGLTF_install_prefix}/inc/")

    foreach(_dir ${_CadExGLTF_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(GLTF "${_dir}")
    endforeach()

    set(CadExGLTF_INCLUDE_DIRS ${_CadExGLTF_OWN_INCLUDE_DIRS})
    set(CadExGLTF_DEFINITIONS "")
    set(CadExGLTF_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(GLTF "Core")

    add_library(CadEx::GLTF SHARED IMPORTED)

    set_property(TARGET CadEx::GLTF PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExGLTF_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(GLTF "${_CadExGLTF_install_prefix}")

    cadex_check_file_exists(GLTF "${CMAKE_CURRENT_LIST_DIR}/CadExGLTFConfigVersion.cmake")

endif()
