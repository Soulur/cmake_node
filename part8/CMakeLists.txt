# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(demo)
# 语言版本
set(CMAKE_CXX_STANDARD 17)


# 定义变量
# 静态库生成的路径
set(LIB_PATH ${PROJECT_SOURCE_DIR}/lib)
# 动态库生成的路径
set(DLL_PATH ${PROJECT_SOURCE_DIR}/dll)
# 可执行程序存储目录
set(EXE_PATH ${PROJECT_SOURCE_DIR}/bin)
# 头文件路径
set(HEAD_PATH ${PROJECT_SOURCE_DIR}/include)

# 库文件的name
set(CALC_NAME calc)
set(SORT_NAME sort)

# 可执行程序的名字
set(APP_NAME app)

# 给当前节点添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)