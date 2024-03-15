# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 语言版本
set(CMAKE_CXX_STANDARD 17)
# 项目名称
project(demo)
# set (SRC
#         main.cpp
# ) set 创建变量，内容为字符串

# 搜索函数 aux_source_directory , file
# aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
file (GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
# 获取头文件位置
include_directories(${PROJECT_SOURCE_DIR}/include)
# 创建可执行文件
add_executable(app ${SRC} )
