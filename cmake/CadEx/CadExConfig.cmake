cmake_minimum_required(VERSION 3.0.2)

if(NOT CadEx_FIND_COMPONENTS)
    set(CadEx_NOT_FOUND_MESSAGE "The CadEx package requires at least one component")
    set(CadEx_FOUND False)
    return()
endif()

set(_CadEx_FIND_PARTS_REQUIRED)
if(CadEx_FIND_REQUIRED)
    set(_CadEx_FIND_PARTS_REQUIRED REQUIRED)
endif()
set(_CadEx_FIND_PARTS_QUIET)
if(CadEx_FIND_QUIETLY)
    set(_CadEx_FIND_PARTS_QUIET QUIET)
endif()
set(_CadEx_FIND_VERSION_EXACT)
if(CadEx_FIND_VERSION_EXACT)
    set(_CadEx_FIND_VERSION_EXACT EXACT)
endif()

get_filename_component(_cadex_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)

set(_CadEx_NOTFOUND_MESSAGE)

include(${CMAKE_CURRENT_LIST_DIR}/CadExModuleLocation.cmake)

foreach(_cadex_module ${CadEx_FIND_COMPONENTS})
    find_package(CadEx${_cadex_module}
        3.9.1 ${_CadEx_FIND_VERSION_EXACT}
        ${_CadEx_FIND_PARTS_QUIET}
        ${_CadEx_FIND_PARTS_REQUIRED}
        PATHS ${_cadex_module_paths} NO_DEFAULT_PATH
    )
    if(NOT CadEx${_cadex_module}_FOUND)
        string(CONFIGURE ${_cadex_module_location_template} _cadex_expected_module_location @ONLY)

        if(CadEx_FIND_REQUIRED_${_cadex_module})
            set(_CadEx_NOTFOUND_MESSAGE "${_CadEx_NOTFOUND_MESSAGE}Failed to find CadEx component \"${_cadex_module}\" config file at \"${_cadex_expected_module_location}\"\n")
        elseif(NOT CadEx_FIND_QUIETLY)
            message(WARNING "Failed to find CadEx component \"${_cadex_module}\" config file at \"${_cadex_expected_module_location}\"")
        endif()

        unset(_cadex_expected_module_location)
    endif()
endforeach()

if(_CadEx_NOTFOUND_MESSAGE)
    set(CadEx_NOT_FOUND_MESSAGE "${_CadEx_NOTFOUND_MESSAGE}")
    set(CadEx_FOUND False)
endif()

cadex_check_file_exists(Core "${CMAKE_CURRENT_LIST_DIR}/CadExConfigVersion.cmake")
