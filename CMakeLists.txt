cmake_minimum_required(VERSION 3.22)
project(TemplateWindow)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
# 设置
set(CMAKE_PREFIX_PATH "C:/Qt/Qt5.14.2/5.14.2/mingw73_64")
# 添加用到的qt库
find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
# 设置目录
aux_source_directory(${PROJECT_SOURCE_DIR} DIR_MAIN_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/resources DIR_RESOURCES_SRCS)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRC_SRCS)

# 添加qrc资源
qt5_add_resources(QRC_FILES resources/img.qrc)

# 配置debug 和 release，release无cmd窗口
IF (CMAKE_BUILD_TYPE STREQUAL Debug)
    add_executable(${PROJECT_NAME}
            resources/app_win32.rc
            ${DIR_MAIN_SRCS} ${DIR_RESOURCES_SRCS} ${DIR_SRC_SRCS}
            ${QRC_FILES})
else(CMAKE_BUILD_TYPE STREQUAL Release)
    add_executable(${PROJECT_NAME}
            WIN32 resources/app_win32.rc ${QRC_FILES}
            ${DIR_MAIN_SRCS} ${DIR_RESOURCES_SRCS} ${DIR_SRC_SRCS} ${QRC_FILES})
ENDIF()

target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

if (WIN32)
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
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
