# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(sort)

# 搜索源文件
aux_source_directory(./ SRC)
# 链接头文件
include_directories(${HEAD_PATH})
# 获取链接动态库的地址
link_directories(${DLL_PATH})

# 存储静态库的地址
set(LIBRARY_OUTPUT_PATH ${LIB_PATH})
# 构造静态库 (SHARED)
add_library(${SORT_NAME} STATIC ${SRC})
# ===========================================

#[[ 
存储动态库的地址
set(LIBRARY_OUTPUT_PATH ${DLL_PATH})
构造动态库 
add_library(${SORT_NAME} SHARED ${SRC}) ]]

# 链接动态库
target_link_libraries(${SORT_NAME} ${CALC_NAME})

