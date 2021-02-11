cmake_minimum_required(VERSION 3.0.2)

set(CadExViewQtQuick_LIBRARIES CadEx::ViewQtQuick)

if(NOT TARGET CadEx::ViewQtQuick)

    if(MSVC10 OR MSVC11)
        message(FATAL_ERROR "The imported target \"CadEx::ViewQtQuick\" is supported in Visual Studio 12 2013 and higher.")
        return()
    endif()

    include("${CMAKE_CURRENT_LIST_DIR}/../helpers/cadex_macros.cmake")

    get_filename_component(_CadExViewQtQuick_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)
    set(_CadExViewQtQuick_OWN_INCLUDE_DIRS "${_CadExViewQtQuick_install_prefix}/inc/")

    foreach(_dir ${_CadExViewQtQuick_OWN_INCLUDE_DIRS})
        cadex_check_file_exists(ViewQtQuick "${_dir}")
    endforeach()

    set(CadExViewQtQuick_INCLUDE_DIRS ${_CadExViewQtQuick_OWN_INCLUDE_DIRS})
    set(CadExViewQtQuick_DEFINITIONS "-D__CADEX_PREVIEW_VISUALIZATION -DCadExViewQtQuick_DLL")
    set(CadExViewQtQuick_COMPILE_DEFINITIONS __CADEX_PREVIEW_VISUALIZATION CadExViewQtQuick_DLL)

    cadex_set_module_dependencies(ViewQtQuick "Core;View")

    # CAD Exchanger Visualization module for Qt is built with Qt 5.12, so it requires Qt at least 5.12 version.
    find_package(Qt5 5.12 COMPONENTS Core Gui OpenGL Quick Qml REQUIRED)
    list(APPEND _CadExViewQtQuick_LIB_DEPENDENCIES Qt5::Core Qt5::Gui Qt5::OpenGL Qt5::Quick Qt5::Qml)

    add_library(CadEx::ViewQtQuick SHARED IMPORTED)

    set_property(TARGET CadEx::ViewQtQuick PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${_CadExViewQtQuick_OWN_INCLUDE_DIRS})
    set_property(TARGET CadEx::ViewQtQuick PROPERTY INTERFACE_COMPILE_DEFINITIONS ${CadExViewQtQuick_COMPILE_DEFINITIONS})

    cadex_add_module_libs(ViewQtQuick "${_CadExViewQtQuick_install_prefix}")

    cadex_check_file_exists(ViewQtQuick "${CMAKE_CURRENT_LIST_DIR}/CadExViewQtQuickConfigVersion.cmake")

endif()
