cmake_minimum_required (VERSION 3.13)
project(offscreen CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core STEP View REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::STEP CadEx::View)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/omni_wheel.stp ${CMAKE_CURRENT_SOURCE_DIR}/omni_wheel.png")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
