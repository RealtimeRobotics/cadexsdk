cmake_minimum_required(VERSION 3.0.2)

set(CadExIFC_LIBRARIES CadEx::IFC)

if(NOT TARGET CadEx::IFC)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExIFC_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExIFC_OWN_INCLUDE_DIRS "${_CadExIFC_install_prefix}/inc/")

    foreach(_dir ${_CadExIFC_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(IFC "${_dir}")
    endforeach()

    set(CadExIFC_INCLUDE_DIRS ${_CadExIFC_OWN_INCLUDE_DIRS})
    set(CadExIFC_DEFINITIONS "")
    set(CadExIFC_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(IFC "Core")

    add_library(CadEx::IFC SHARED IMPORTED)

    set_property(TARGET CadEx::IFC PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExIFC_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(IFC "${_CadExIFC_install_prefix}")

    cadex_check_file_exists(IFC "${CMAKE_CURRENT_LIST_DIR}/CadExIFCConfigVersion.cmake")

endif()
