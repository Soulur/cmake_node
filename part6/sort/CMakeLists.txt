# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(sort)

# 搜索源文件
aux_source_directory(./ SRC)
# 链接头文件
include_directories(${HEAD_PATH})

set(LIBRARY_OUTPUT_PATH ${DLL_PATH})
# 构造动态库
add_library(${SORT_NAME} SHARED ${SRC})