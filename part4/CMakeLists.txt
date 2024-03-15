# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 语言版本
set(CMAKE_CXX_STANDARD 17)
# 项目名称
project(demo)
# 将可执行文件放在 bin
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# 搜索 .cpp 文件
file(GLOB SRC ${PROJECT_SOURCE_DIR}/*.cpp)
# 日志
message("======================================================================")
# 用 set 创建 list
set(T a;b;c;d;e)
message("message: "${T})
message("======================================================================")
# 追加字符串
set(TT a;b;c;d;e)
list(APPEND T ${TT} )
message("message: "${T})
message("======================================================================")
# 删除字符串
file(GLOB NAME ${PROJECT_SOURCE_DIR}/src/*.cpp)
message("message: "${NAME})
list (REMOVE_ITEM NAME ${PROJECT_SOURCE_DIR}/src/c1.cpp)
message("======================================================================")
message("message: "${NAME})
message("======================================================================")
# 创建可执行文件
add_executable(app ${SRC})