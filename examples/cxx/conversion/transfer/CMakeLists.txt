cmake_minimum_required (VERSION 3.13)
project(transfer CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core JT STEP REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::JT CadEx::STEP)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/omni_wheel.stp ${CMAKE_CURRENT_SOURCE_DIR}/omni_wheel.jt")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
