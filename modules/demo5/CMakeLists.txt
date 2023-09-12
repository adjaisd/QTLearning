set(MODULE_NAME demo5)

add_executable(${MODULE_NAME})

set(DEPENDENCIES Core Gui Widgets)
find_package(Qt6 COMPONENTS ${DEPENDENCIES} REQUIRED)

file(GLOB INC include/*.h)
file(GLOB SRC src/*.cpp)
file(GLOB IMP impl/*.cpp)

set(QRC_FILES resources/src.qrc)
qt_add_resources(${QRC_FILES})

#国际化: https://www.cnblogs.com/apocelipes/p/14355460.html
set(LUPDATE C:/software/QT/6.5.2/mingw_64/bin/lupdate.exe)
set(LRELEASE C:/software/QT/6.5.2/mingw_64/bin/lrelease.exe)

set(SRC_LANG en-US)
set(DST_LANG zh-CN)
set(TS_FILES resources/lang/zh_CN.ts)
# 创建生成ts文件和qm文件的目标，ALL指定加入make all
add_custom_target(update_all_ts_files ALL)
add_custom_target(create_all_qm_files ALL)
# 对于每一个ts文件，都生成一个update_ts_file_<NAME>和create_qm_file_<NAME>目标
foreach (TS_FILE ${TS_FILES})
    # 把zh_CN.ts中的zh_CN提取出来
    get_filename_component(I18N_NAME ${TS_FILE} NAME_WE)
    set(TS_TARGET_NAME "update_ts_file_${I18N_NAME}")   # TS_TARGET_NAME
    set(QM_TARGET_NAME "create_qm_file_${I18N_NAME}")   # QM_TARGET_NAME
    add_custom_target(
            ${TS_TARGET_NAME}
            COMMAND ${LUPDATE} ${CMAKE_CURRENT_SOURCE_DIR}
            -locations none  # none relative absolute
            -ts ${TS_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "生成ts文件"
            VERBATIM
    )
    # 将update_ts_file_<NAME>添加为update_all_ts_files的依赖，下同
    add_dependencies(update_all_ts_files ${TS_TARGET_NAME})
    set(QM_FILE "${CMAKE_BINARY_DIR}/bin/${I18N_NAME}.qm")
    add_custom_target(${QM_TARGET_NAME}
            COMMAND ${LRELEASE} ${TS_FILE} -qm ${QM_FILE}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "生成qm文件"
            VERBATIM)
    # 因为得先有ts文件才能生成qm文件，所以把构建ts文件的目标作为自己的依赖
    add_dependencies(${QM_TARGET_NAME} ${TS_TARGET_NAME})
    add_dependencies(create_all_qm_files ${QM_TARGET_NAME})
endforeach ()

add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/bin/translations.qrc
        COMMAND ${CMAKE_COMMAND} -E copy
        resources/translations.qrc
        ${CMAKE_BINARY_DIR}/bin
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "拷贝qrc到bin目录" VERBATIM)

# 因为qrc依赖qm文件，所以需要先让qm文件创建完成
add_dependencies(${MODULE_NAME} create_all_qm_files)

target_sources(${MODULE_NAME}
        PUBLIC ${INC} ${SRC} ${UI} ${QRC_FILES}
        ${CMAKE_BINARY_DIR}/bin/translations.qrc
        PRIVATE ${IMP})

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
                "${CMAKE_BINARY_DIR}/bin/plugins/platforms/")
        add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "${CMAKE_BINARY_DIR}/bin/plugins/platforms/")
    endif ()
    foreach (QT_LIB ${DEPENDENCIES})
        add_custom_command(TARGET ${MODULE_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "${CMAKE_BINARY_DIR}/bin")
    endforeach (QT_LIB)
endif ()