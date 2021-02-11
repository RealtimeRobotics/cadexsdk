cmake_minimum_required(VERSION 3.0.2)

set(CadExRhino_LIBRARIES CadEx::Rhino)

if(NOT TARGET CadEx::Rhino)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExRhino_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExRhino_OWN_INCLUDE_DIRS "${_CadExRhino_install_prefix}/inc/")

    foreach(_dir ${_CadExRhino_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(Rhino "${_dir}")
    endforeach()

    set(CadExRhino_INCLUDE_DIRS ${_CadExRhino_OWN_INCLUDE_DIRS})
    set(CadExRhino_DEFINITIONS "")
    set(CadExRhino_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(Rhino "Core")

    add_library(CadEx::Rhino SHARED IMPORTED)

    set_property(TARGET CadEx::Rhino PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExRhino_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(Rhino "${_CadExRhino_install_prefix}")

    cadex_check_file_exists(Rhino "${CMAKE_CURRENT_LIST_DIR}/CadExRhinoConfigVersion.cmake")

endif()
