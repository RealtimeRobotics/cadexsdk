cmake_minimum_required(VERSION 3.0.2)

set(CadExPRC_LIBRARIES CadEx::PRC)

if (NOT TARGET CadEx::PRC)

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExPRC_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExPRC_OWN_INCLUDE_DIRS "${_CadExPRC_install_prefix}/inc/")

    foreach(_dir ${_CadExPRC_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(PRC "${_dir}")
    endforeach()

    set(CadExPRC_INCLUDE_DIRS ${_CadExPRC_OWN_INCLUDE_DIRS})
    set(CadExPRC_DEFINITIONS "")
    set(CadExPRC_COMPILE_DEFINITIONS "")

    cadex_set_module_dependencies(PRC "Core")

    add_library(CadEx::PRC SHARED IMPORTED)

    set_property(TARGET CadEx::PRC PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExPRC_OWN_INCLUDE_DIRS})

    cadex_add_module_libs(PRC "${_CadExPRC_install_prefix}")

    cadex_check_file_exists(PRC "${CMAKE_CURRENT_LIST_DIR}/CadExPRCConfigVersion.cmake")

endif()
