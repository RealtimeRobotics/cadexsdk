cmake_minimum_required(VERSION 3.0.2)

set(CadExPara_LIBRARIES CadEx::Para)

if(NOT TARGET CadEx::Para)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExPara_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExPara_OWN_INCLUDE_DIRS "${_CadExPara_install_prefix}/inc/")

    foreach(_dir ${_CadExPara_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(Para "${_dir}")
    endforeach()

    set(CadExPara_INCLUDE_DIRS ${_CadExPara_OWN_INCLUDE_DIRS})
    set(CadExPara_DEFINITIONS "")
    set(CadExPara_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(Para "Core")

    add_library(CadEx::Para SHARED IMPORTED)

    set_property(TARGET CadEx::Para PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExPara_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(Para "${_CadExPara_install_prefix}")

    cadex_check_file_exists(Para "${CMAKE_CURRENT_LIST_DIR}/CadExParaConfigVersion.cmake")

endif()
