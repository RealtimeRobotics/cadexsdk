if (MSVC_IDE)
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

    unset(PROJECT_FOLDER)
    get_filename_component(DIRECTORY_PATH "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)
    while (true)
        get_filename_component(DIRECTORY_NAME "${DIRECTORY_PATH}" NAME)
        if (NOT DIRECTORY_NAME OR DIRECTORY_NAME STREQUAL "cxx" OR DIRECTORY_NAME STREQUAL "csharp")
            break()
        endif()
        list(APPEND PROJECT_FOLDER "${DIRECTORY_NAME}")
        get_filename_component(DIRECTORY_PATH "${DIRECTORY_PATH}" DIRECTORY)
    endwhile()

    if(CADEX_MSVC_IDE_EXAMPLE_FOLDER)
        list(APPEND PROJECT_FOLDER "${CADEX_MSVC_IDE_EXAMPLE_FOLDER}")
    endif()
    list(REVERSE PROJECT_FOLDER)
    list(JOIN PROJECT_FOLDER "/" PROJECT_FOLDER)

    set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "${PROJECT_FOLDER}"
        VS_DEBUGGER_ENVIRONMENT "PATH=${CADEX_ROOT_DIR}/win$<IF:$<EQUAL:4,${CMAKE_SIZEOF_VOID_P}>,32,64>/${COMPILER}/bin$<$<CONFIG:Debug>:d>;${QT_ROOT_DIR}/bin;%PATH%"
        VS_DEBUGGER_COMMAND_ARGUMENTS "${CADEX_RUN_ARGUMENTS}")

endif()
