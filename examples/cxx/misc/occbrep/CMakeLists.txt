cmake_minimum_required (VERSION 3.13)

if(NOT OCC_INCLUDE_DIR OR NOT OCC_LIBRARY_DIR)
    message(WARNING "cadexocc example requries OCC_INCLUDE_DIR and OCC_LIBRARY_DIR variables to be set. Skipping.")
    return()
endif()

project(occbrep CXX)

file(GLOB SRC "*xx")
add_executable(${PROJECT_NAME} ${SRC})

find_package(CadEx COMPONENTS Core REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CadEx::Core)

# You can use occ cmake find system.
# list(APPEND CMAKE_PREFIX_PATH "${OCC_ROOT_DIR}/cmake")
# find_package(OpenCASCADE COMPONENTS FoundationClasses ModelingData ModelingAlgorithms REQUIRED)
# In current example find libraries directly
target_include_directories(${PROJECT_NAME} PRIVATE "${OCC_INCLUDE_DIR}")
set(_occ_libs TKBRep TKernel TKMath TKTopAlgo TKPrim)
foreach(_occ_lib ${_occ_libs})
    find_library(${_occ_lib} NAMES ${_occ_lib}
                             PATHS "${OCC_LIBRARY_DIR}")
    if (NOT ${_occ_lib})
        message(FATAL_ERROR "Unable to find ${_occ_lib} in ${OCC_LIBRARY_DIR}")
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${${_occ_lib}})
endforeach()

include("${CADEX_ROOT_DIR}/examples/cmake/extra.cmake")
