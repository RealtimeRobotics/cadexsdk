cmake_minimum_required (VERSION 3.13)
project(propertytable CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/as1.xml")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
