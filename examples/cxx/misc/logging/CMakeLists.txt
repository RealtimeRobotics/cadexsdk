cmake_minimum_required (VERSION 3.13)
project(logging CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core ACIS REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::ACIS)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/transmissionhousing1.sat")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
