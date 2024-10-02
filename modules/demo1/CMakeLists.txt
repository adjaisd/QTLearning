set(MODULE_NAME demo1)

#find_package(Qt6 COMPONENTS Core Gui Widgets Network REQUIRED)
set(DEPENDENCIES Core Gui Widgets Network)
find_package(Qt6 COMPONENTS ${DEPENDENCIES} REQUIRED)

file(GLOB INC include/*.h)  # 接口头文件
file(GLOB SRC src/*.cpp)    # 主模块
file(GLOB IMP impl/*.cpp)   # 接口实现
file(GLOB UI ui/*.ui)       # ui文件
qt6_wrap_ui(UI_HEADERS ${UI})

add_executable(${MODULE_NAME})
# 多资源文件 https://blog.csdn.net/qq_51470638/article/details/129101424
set_target_properties(${MODULE_NAME} PROPERTIES AUTOMOC ON)
set_target_properties(${MODULE_NAME} PROPERTIES AUTORCC ON)
set_target_properties(${MODULE_NAME} PROPERTIES AUTOUIC ON)

# 设置自动搜索路径
set_target_properties(${MODULE_NAME} PROPERTIES AUTOUIC_SEARCH_PATHS ui)

# 资源文件  https://zhuanlan.zhihu.com/p/519409942
set(QRC_RESOURCE_FILES resources/src.qrc)
qt_add_resources(${QRC_RESOURCE_FILES})

# 注意:
# 在链接时，如果将头文件与头文件及实现放在不同的目录下，则target_sources必须必须明确有头文件，否则报错` undefined reference to `vtable for xxx'`
target_sources(${MODULE_NAME}
        PUBLIC ${INC} ${SRC} ${UI} ${UI_HEADERS} ${QRC_RESOURCE_FILES}
        PRIVATE ${IMP})

target_include_directories(${MODULE_NAME} PUBLIC include ${CMAKE_CURRENT_SOURCE_DIR})

#target_link_libraries(${MODULE_NAME} Qt::Core Qt::Gui Qt::Widgets Qt::Network)
foreach (DEPEND ${DEPENDENCIES})
    target_link_libraries(${MODULE_NAME} PUBLIC Qt::${DEPEND})
endforeach ()

# 解决缺少dll问题
# dll文件拷贝到build目录下的bin路径
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