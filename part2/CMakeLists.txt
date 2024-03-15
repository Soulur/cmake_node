# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 语言版本
set(CMAKE_CXX_STANDARD 17)
# 项目名称
project(demo)

# 获取头文件位置
include_directories(${PROJECT_SOURCE_DIR}/include)
# 搜索 cpp文件 用于创建库
file (GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp)

# add_executable(app ${SRC} ) 创建库文件时，不需要可执行文件

# 静态库
add_library(calc1 STATIC ${SRC})
# 动态库
add_library(calc2 SHARED ${SRC})
# 将库保存的位置，静动都适用
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)