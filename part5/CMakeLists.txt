# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 语言版本
set(CMAKE_CXX_STANDARD 17)
# 项目名称
project(demo)
# 将可执行文件放在 bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp)


# -D宏定义 则执行 #ifdef 的内容 (注释则相当于把文件中的 DEBUG 删除掉了)
add_definitions(-DDEBUG)

add_executable(app ${SRC})

