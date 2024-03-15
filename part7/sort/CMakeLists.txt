# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(sort)

# 搜索源文件
aux_source_directory(./ SRC)
# 链接头文件
include_directories(${HEAD_PATH})
# 静态库存储位置
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
# 链接静态库
link_libraries(${CALC_NAME})
link_directories(${LIB_PATH})
# 构造静态库 (SHARED)
add_library(${SORT_NAME} STATIC ${SRC})