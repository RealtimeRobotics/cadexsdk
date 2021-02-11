cmake_minimum_required (VERSION 3.13)
project(progressindicatorgui CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core ACIS REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::ACIS)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
qt5_wrap_cpp(MOCS importdialog.hxx)
target_sources(${PROJECT_NAME} PRIVATE ${MOCS})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)

include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
