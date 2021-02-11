cmake_minimum_required (VERSION 3.13)
project(remeshing CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core SLD VRML REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core CadEx::SLD CadEx::VRML)

set(CADEX_RUN_ARGUMENTS "${CADEX_EXAMPLES_MODELS_DIR}/CAPACITOR.SLDPRT ${CMAKE_CURRENT_SOURCE_DIR}/CAPACITOR.wrl")
include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
