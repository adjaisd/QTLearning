set(MODULE_NAME demo2)

set(DEPENDENCIES Core Gui Widgets)
find_package(Qt6 COMPONENTS ${DEPENDENCIES} REQUIRED)

file(GLOB INC include/*.h)
file(GLOB SRC src/*.cpp)
file(GLOB IMP impl/*.cpp)

add_executable(${MODULE_NAME})

target_sources(
        ${MODULE_NAME}
        PUBLIC ${INC} ${SRC}
        PRIVATE ${IMP}
)

target_include_directories(${MODULE_NAME} PUBLIC include)

foreach (DEPEND ${DEPENDENCIES})
    target_link_libraries(${MODULE_NAME} PUBLIC Qt::${DEPEND})
endforeach ()

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins/platforms/")
        add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins/platforms/")
    endif ()
    foreach (QT_LIB ${DEPENDENCIES})
        add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    endforeach (QT_LIB)
endif ()