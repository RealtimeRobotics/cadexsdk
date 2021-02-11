function(cadex_get_platform_lib_path OUTVAR)

    math(EXPR COMPILER_BITNESS "8*${CMAKE_SIZEOF_VOID_P}")

    if(ANDROID)
        set(ARCH "arm${COMPILER_BITNESS}")
    else()
        set(ARCH ${COMPILER_BITNESS})
    endif()

    if(MSVC)
        if(MSVC10)
            set(COMPILER vc10)
        elseif(MSVC11)
            set(COMPILER vc11)
        elseif(MSVC12)
            set(COMPILER vc12)
        elseif(MSVC14)
            if(MSVC_VERSION EQUAL 1900)
                set(COMPILER vc14)
            else() # Visual Studio 2017
                set(COMPILER vc14.1)
            endif()
        endif()
    elseif(DEFINED CMAKE_COMPILER_IS_GNUCC)
        string(REGEX MATCHALL "[0-9]+" CXX_VERSION_COMPONENTS ${CMAKE_CXX_COMPILER_VERSION})
        list(GET CXX_VERSION_COMPONENTS 0 GCC_MAJOR)
        if (${GCC_MAJOR} GREATER 7)
            set(GCC_MAJOR 7)
        endif()
        set(COMPILER "gcc${GCC_MAJOR}")
    elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
        string(REGEX MATCHALL "[0-9]+" CXX_VERSION_COMPONENTS ${CMAKE_CXX_COMPILER_VERSION})
        list(GET CXX_VERSION_COMPONENTS 0 CLANG_MAJOR)
        if(APPLE)
            if (${CLANG_MAJOR} GREATER_EQUAL 10)
                set(CLANG_MAJOR 10)
            elseif(${CLANG_MAJOR} GREATER 7)
                set(CLANG_MAJOR 7)
            endif()
            set(COMPILER "clang${CLANG_MAJOR}")
        elseif(ANDROID)
            if (${CLANG_MAJOR} GREATER 7)
                set(CLANG_MAJOR 7)
            endif()
            set(COMPILER "clang${CLANG_MAJOR}")
        else()
            set(COMPILER "gcc7")
        endif()
    else()
        set(COMPILER ${CMAKE_GENERATOR})
        string(REGEX REPLACE " " "" COMPILER ${COMPILER})
    endif()

    # detect host OS
    if(WIN32)
        set(HOST_OS "win")
    elseif(APPLE)
        set(HOST_OS "mac")
    elseif(ANDROID)
        set(HOST_OS "and")
    else()
        set(HOST_OS "lin")
    endif()

    set(${OUTVAR} "${HOST_OS}${ARCH}/${COMPILER}" PARENT_SCOPE)

endfunction()

macro(cadex_check_file_exists Module File)

    if(NOT EXISTS "${File}" )
        message(FATAL_ERROR "The imported target \"CadEx::${Module}\" references the file
   \"${File}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()

endmacro()

macro(cadex_set_module_dependencies Module Deps)

    set(_CadEx${Module}_FIND_DEPENDENCIES_REQUIRED)
    if(CadEx${Module}_FIND_REQUIRED)
        set(_CadEx${Module}_FIND_DEPENDENCIES_REQUIRED REQUIRED)
    endif()

    set(_CadEx${Module}_FIND_DEPENDENCIES_QUIET)
    if(CadEx${Module}_FIND_QUIETLY)
        set(_CadEx${Module}_DEPENDENCIES_FIND_QUIET QUIET)
    endif()

    set(_CadEx${Module}_FIND_VERSION_EXACT)
    if(CadEx${Module}_FIND_VERSION_EXACT)
        set(_CadEx${Module}_FIND_VERSION_EXACT EXACT)
    endif()

    foreach(_module_dep ${Deps})
        if(NOT CadEx${_module_dep}_FOUND)
            find_package(CadEx${_module_dep}
                3.9.1 ${_CadEx${Module}_FIND_VERSION_EXACT}
                ${_CadEx${Module}_DEPENDENCIES_FIND_QUIET}
                ${_CadEx${Module}_FIND_DEPENDENCIES_REQUIRED}
                PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH)
        endif()

        if(NOT CadEx${_module_dep}_FOUND)
            set(CadEx${Module}_FOUND False)
            return()
        endif()

        list(APPEND CadEx${Module}_INCLUDE_DIRS "${CadEx${_module_dep}_DEFINITIONS}")
        list(APPEND CadEx${Module}_DEFINITIONS ${CadEx${_module_dep}_DEFINITIONS})
        list(APPEND CadEx${Module}_COMPILE_DEFINITIONS ${CadEx${_module_dep}_COMPILE_DEFINITIONS})
        list(APPEND CadEx${Module}_EXECUTABLE_COMPILE_FLAGS ${CadEx${_module_dep}_EXECUTABLE_COMPILE_FLAGS})
        list(APPEND _CadEx${Module}_LIB_DEPENDENCIES CadEx::${_module_dep})
    endforeach()

    list(REMOVE_DUPLICATES CadEx${Module}_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES CadEx${Module}_DEFINITIONS)
    list(REMOVE_DUPLICATES CadEx${Module}_COMPILE_DEFINITIONS)

endmacro()

macro(cadex_add_module_configuration Module Configuration Lib)

    cadex_check_file_exists("${Module}" "${Lib}")

    set_property(TARGET "CadEx::${Module}" APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})
    set_property(TARGET "CadEx::${Module}" PROPERTY INTERFACE_LINK_LIBRARIES "${_CadEx${Module}_LIB_DEPENDENCIES}")
    if(MSVC)
        set_property(TARGET "CadEx::${Module}" PROPERTY IMPORTED_IMPLIB_${Configuration} "${Lib}")
    else()
        set_property(TARGET "CadEx::${Module}" PROPERTY IMPORTED_LOCATION_${Configuration} "${Lib}")
    endif()

endmacro()

macro(cadex_add_module_libs Module LibPaths)

    cadex_get_platform_lib_path(_cadex_lib_path)

    if(MSVC)
        set(DEBUG_SUFFIX "d")
    endif()
    find_library(_CadEx${Module}_deb_library CadEx${Module}${DEBUG_SUFFIX}  PATHS ${_CadEx${Module}_install_prefix} PATH_SUFFIXES ${_cadex_lib_path}/lib${DEBUG_SUFFIX} NO_DEFAULT_PATH)
    find_library(_CadEx${Module}_rel_library CadEx${Module}                 PATHS ${_CadEx${Module}_install_prefix} PATH_SUFFIXES ${_cadex_lib_path}/lib                NO_DEFAULT_PATH)

    cadex_add_module_configuration(${Module} DEBUG "${_CadEx${Module}_deb_library}")
    cadex_add_module_configuration(${Module} RELEASE "${_CadEx${Module}_rel_library}")
    cadex_add_module_configuration(${Module} RELWITHDEBINFO "${_CadEx${Module}_rel_library}")

endmacro()
