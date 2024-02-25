# [【Qt CMake】解析QT6 CMake文件](https://zhuanlan.zhihu.com/p/630034777)

cmake_minimum_required(VERSION 3.5)         # 需要的CMake最低版本

project(qt-samp1 VERSION 0.1 LANGUAGES CXX)  # 项目名称 版本 编程语言

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)       # UIC能被自动执行
set(CMAKE_AUTOMOC ON)       # MOC能被自动执行
set(CMAKE_AUTORCC ON)       # RCC能被自动执行

set(CMAKE_CXX_STANDARD 17)  # 设置编译器需要满足的C++语言标准
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 要求编译器满足 C++标准

# cmake .. #试找 Qt6 失败则用 Qt5
# cmake .. -DQT_VERSION_MAJOR=5 #强制使用 Qt5
# cmake .. -DQT_VERSION_MAJOR=6 #强制使用 Qt6
if (NOT DEFINED QT_VERSION_MAJOR)
    message("NOT DEFINED QT_VERSION_MAJOR , try find_package(QT NAMES Qt6 Qt5)")
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
    message("Found QT_VERSION_MAJOR = " ${QT_VERSION_MAJOR})
else()
    message("DEFINED QT_VERSION_MAJOR = " ${QT_VERSION_MAJOR})
endif()
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets REQUIRED)
find_package(fmt REQUIRED)

# 设置变量 PROJECT_SOURCES 等于下面的列表
set(PROJECT_SOURCES
    main.cpp
    MainWindow.h
    MainWindow.cpp
    MainWindow.ui
)

# 创建可执行文件
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif()

# 连接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    fmt::fmt
)

# 设置目标可执行文件的属性，如MacOSX的Bundle标识符、版本号和短版本字符串，以及在Windows下作为可执行文件运行。
set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_finalize_target(${PROJECT_NAME})
endif()
