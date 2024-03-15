# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(test2)

# 搜索 .cpp 文件
aux_source_directory(./ SRC)
# 链接头文件
include_directories(${HEAD_PATH})

# 链接静态库
link_directories(${DLL_PATH})
link_libraries(${SORT_NAME})

# 创建可执行文件
set(EXECUTABLE_OUTPUT_PATH ${EXE_PATH})
add_executable(${APP2_NAME} ${SRC})