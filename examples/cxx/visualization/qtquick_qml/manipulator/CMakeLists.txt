cmake_minimum_required (VERSION 3.13)
project(manipulator_qtquick_qml CXX)

file(GLOB SRC "*xx")
file(GLOB SRC2 "../baseviewer/*xx")
list(FILTER SRC2 EXCLUDE REGEX "/baseviewer/main.cxx$")
list(APPEND SRC ${SRC2})

add_executable(${PROJECT_NAME} WIN32 ${SRC})

find_package(CadEx COMPONENTS Core View ViewQtQuick STEP REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::View CadEx::ViewQtQuick CadEx::STEP)

find_package(Qt5 COMPONENTS Core Gui Qml Quick Widgets REQUIRED)
qt5_wrap_cpp(MOCS ManipulatorApplication.hxx 
                  ../baseviewer/BaseViewerApplication.hxx)
qt5_add_resources(QRCS resources/ManipulatorQml.qrc
                       ../baseviewer/resources/BaseQml.qrc
                       ../baseviewer/resources/BaseViewerQml.qrc)
target_sources(${PROJECT_NAME} PRIVATE ${MOCS} ${QRCS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)
if(ANDROID)
    find_package(Qt5 COMPONENTS AndroidExtras REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::AndroidExtras)
endif()

include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
