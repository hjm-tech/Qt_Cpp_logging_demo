cmake_minimum_required(VERSION 3.16)
project(demo2)
# Qt自动工具（MOC/UIC/RCC）
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 重点：寻找Qt6，组件Widgets（包含QApplication、QPushButton）
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
add_executable(running main.cpp)
# 链接Qt库
target_link_libraries(running PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)