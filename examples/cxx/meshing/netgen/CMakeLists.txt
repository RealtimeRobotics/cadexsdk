cmake_minimum_required (VERSION 3.13)
project(netgen CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core Mesh REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::Mesh)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/LeverArm.xml")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
