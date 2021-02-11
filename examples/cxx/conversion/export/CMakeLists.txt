cmake_minimum_required (VERSION 3.13)
project(export CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core OBJ REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::OBJ)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/as1.xml ${CMAKE_CURRENT_SOURCE_DIR}/as1.obj")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
