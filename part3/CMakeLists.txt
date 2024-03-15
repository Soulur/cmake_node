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

# # 获取头文件位置
include_directories(${PROJECT_SOURCE_DIR}/include)
# 获取库文件的位置
link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/dll)

# 链接静态库
link_libraries(calc1)
# 创建可执行文件
add_executable(app ${SRC} )

#链接动态库 (推荐放在最后)
target_link_libraries(app calc2) 




