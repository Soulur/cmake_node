

## CMake概述

CMake 是一个项目构建工具，并且是跨平台的。关于项目构建我们所熟知的还有Makefile（通过 make 命令进行项目的构建），大多是IDE软件都集成了make，比如：VS 的 nmake、linux 下的 GNU make、Qt 的 qmake等，如果自己动手写 makefile，会发现，makefile 通常依赖于当前的编译平台，而且编写 makefile 的工作量比较大，解决依赖关系时也容易出错。

而 CMake 恰好能解决上述问题， 其允许开发者指定整个工程的编译流程，在根据编译平台，自动生成本地化的Makefile和工程文件，最后用户只需make编译即可，所以可以把CMake看成一款自动生成 Makefile的工具。

介绍完CMake的作用之后，再来总结一下它的优点：

- 跨平台
- 能够管理大型项目
- 简化编译构建过程和编译过程
- 可扩展：可以为 cmake 编写特定功能的模块，扩充 cmake 功能



## CMake的基本使用

CMake支持大写、小写、混合大小写的命令。如果在编写CMakeLists.txt文件时使用的工具有对应的命令提示，那么大小写随缘即可，不要太过在意。

### 注释
注释行
CMake 使用 # 进行行注释，可以放在任何位置。

```cmake
# 这是一个 CMakeLists.txt 文件
```

注释块
CMake 使用 #[[ ]] 形式进行块注释。

```cmake
#[[ 这是一个 CMakeLists.txt 文件。
这是一个 CMakeLists.txt 文件
这是一个 CMakeLists.txt 文件 ]]
```

### 基础构造

指定使用的 cmake 的最低版本 (可选，非必须，如果不加可能会有警告)

```cmake
cmake_minimum_required(VERSION 3.26)
```

定义工程名称，并可指定工程的版本、工程描述、web主页地址、支持的语言（默认情况支持所有语言），如果不需要这些都是可以忽略的，只需要指定出工程名字即可。

```cmake
project(<PROJECT-NAME> [<language-name>...])
project(<PROJECT-NAME> # 工程名称
       [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]] # 工程版本
       [DESCRIPTION <project-description-string>] # 工程描述
       [HOMEPAGE_URL <url-string>] # web主页地址
       [LANGUAGES <language-name>...]) # 支持的语言
```

定义工程会生成一个可执行程序

``` cmake
add_executable("exe" ".cpp")
```

程序在编译过程中还会生成一些中间文件和一个可执行文件，这样会导致整个项目目录看起来很混乱，不太容易管理和维护，此时我们就可以把生成的这些与项目源码无关的文件统一放到一个对应的目录里边，比如将这个目录命名为 build

```shell
$ mkdir build
$ cd build
$ cmake ..
$ make
```

此时我们就需要定义一个变量，将文件名对应的字符串存储起来，在cmake里定义变量需要使用set。

```cmake
# SET 指令的语法是：
# [] 中的参数为可选项, 如不需要可以不写
SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
# - VAR：变量名
# - VALUE：变量值
```

 指定使用的C++标准

```cmake
set(CMAKE_CXX_STANDARD 11) # 11 17 20
```

指定输出的路径

在CMake中指定可执行程序输出的路径，也对应一个宏，叫做EXECUTABLE_OUTPUT_PATH，它的值还是通过set命令进行设置:

```cmake
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
```

搜索文件

- aux_source_directory  
- file

``` cmake
# [[ aux_source_directory(< dir > < name >)
# dir：要搜索的目录
# name：将从dir目录下搜索到的源文件列表存储到该变量中 ]]
aux_source_directory(${PROJECT_SOURCE_DIR} SRC)
```

```cmake
# [ file(GLOB/GLOB_RECURSE 变量名 要搜索的文件路径和文件类型) ]
# - GLOB  当前文件夹搜索
# - GLOB_RECURSE  递归搜索
file(GLOB SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
```

将源文件对应的头文件路径指定出来，这样才能保证在编译过程中编译器能够找到这些头文件，并顺利通过编译

```cmake
include_directories(${PROJECT_SOURCE_DIR}/include)
```



## 动态库、静态库

有些时候我们编写的源代码并不需要将他们编译生成可执行程序，而是生成一些静态库或动态库提供给第三方使用，下面来讲解在cmake中生成这两类库文件的方法。

```shell
.
├── build
├── CMakeLists.txt
├── include           # 头文件目录
│   └── head.h
├── main.cpp          # 用于测试的源文件
└── src               # 源文件目录
    ├── add.cpp
    ├── div.cpp
    ├── mult.cpp
    └── sub.cpp
```

### 制作静态库

在cmake中，如果要制作静态库，需要使用的命令如下

```cmake
add_library(库名称 STATIC 源文件1 [源文件2] ...) 
```

在Linux中，静态库名字分为三部分：lib + 库名字 +.a，此处只需要指定出库的名字就可以了，另外两部分在生成该文件的时候会自动填充。

在Windows中虽然库名和Linux格式不同，但也只需指定出名字即可。

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(calc STATIC ${SRC_LIST})
```

这样最终就会生成对应的静态库文件 libcalc.a。

### 制作动态库

在cmake中，如果要制作动态库，需要使用的命令如下：

```cmake
add_library(库名称 SHARED 源文件1 [源文件2] ...) 
```

在Linux中，动态库名字分为三部分：lib+库名字+.so，此处只需要指定出库的名字就可以了，另外两部分在生成该文件的时候会自动填充。

在Windows中虽然库名和Linux格式不同，但也只需指定出名字即可。

根据上面的目录结构，可以这样编写CMakeLists.txt文件:

```cmake
cmake_minimum_required(VERSION 3.0)
project(CALC)
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(calc SHARED ${SRC_LIST})
```

这样最终就会生成对应的动态库文件libcalc.so。

### 指定输出的路径

对于生成的库文件来说和可执行程序一样都可以指定输出路径

```cmake
# 设置动态库生成路径 
# - EXECUTABLE_OUTPUT_PATH (只适用于动态库)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/dll)
```

静，动都适用

```cmake
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB SRC_LIST "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# 设置动态库/静态库生成路径
# - LIBRARY_OUTPUT_PATH
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 生成动态库
add_library(calc SHARED ${SRC_LIST})
# 生成静态库
add_library(calc STATIC ${SRC_LIST})
```

### 链接库文件

在编写程序的过程中，可能会用到一些系统提供的动态库或者自己制作出的动态库或者静态库文件，cmake中也为我们提供了相关的加载动态库的命令。

#### link_directories

link_directories 只能链接静态库

```shell
$ tree 
.
├── build
├── CMakeLists.txt
├── include
│   └── head.h
├── lib
│   └── libcalc.a     # 制作出的静态库的名字
└── src
    └── main.cpp
```

在cmake中，链接静态库的命令如下：

```cmake
# - link_libraries(<static lib> [<static lib>...])
# - <static lib> ：指定出要链接的静态库的名字 (可以是全名 libxxx.a 也可以是掐头（lib）去尾（.a）之后的名字 xxx )
# - [<static lib>...]：要链接的其它静态库的名字
```

```cmake
link_directories(<lib path>)
```

这样，修改之后的CMakeLists.txt文件内容如下:

```cmake
# 包含静态库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
# 链接静态库
link_libraries(calc)
```

#### target_link_libraries

关于动态库的制作、使用以及在内存中的加载方式和静态库都是不同的

在 cmake 中链接动态库的命令如下:

```cmake
# - target_link_libraries(
    <target> 
    <PRIVATE|PUBLIC|INTERFACE> <item>... 
    [<PRIVATE|PUBLIC|INTERFACE> <item>...]...)
# target：指定要加载动态库的文件的名字
	# 该文件可能是一个源文件
	# 该文件可能是一个动态库文件
	# 该文件可能是一个可执行文件
# PRIVATE|PUBLIC|INTERFACE：动态库的访问权限，默认为PUBLIC
```

如果各个动态库之间没有依赖关系，无需做任何设置，三者没有没有区别，一般无需指定，使用默认的 PUBLIC 即可。

动态库的链接具有传递性，如果动态库 A 链接了动态库B、C，动态库D链接了动态库A，此时动态库D相当于也链接了动态库B、C，并可以使用动态库B、C中定义的方法。

```cmake
target_link_libraries(A B C)
target_link_libraries(D A)
```

```toml
PUBLIC：在public后面的库会被Link到前面的target中，并且里面的符号也会被导出，提供给第三方使用。
PRIVATE：在private后面的库仅被link到前面的target中，并且终结掉，第三方不能感知你调了啥库
INTERFACE：在interface后面引入的库不会被链接到前面的target中，只会导出符号。
```

链接系统动态库

动态库的链接和静态库是完全不同的：

- 静态库会在生成可执行程序的链接阶段被打包到可执行程序中，所以可执行程序启动，静态库就被加载到内存中了。
- 动态库在生成可执行程序的链接阶段不会被打包到可执行程序中，当可执行程序被启动并且调用了动态库中的函数的时候，动态库才会被加载到内存

因此，在cmake中指定要链接的动态库的时候，应该将命令写到生成了可执行文件之后：

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 添加并指定最终生成的可执行程序名
add_executable(app ${SRC_LIST})
# 指定可执行程序要链接的动态库名字
target_link_libraries(app pthread)

# 在target_link_libraries(app pthread)中：

# [[
app: 对应的是最终生成的可执行程序的名字
pthread：这是可执行程序要加载的动态库，这个库是系统提供的线程库，全名为libpthread.so，在指定的时候一般会掐头（lib）去尾（.so）。 ]]
```

链接第三方动态库

假设在测试文件main.cpp中既使用了自己制作的动态库libcalc.so又使用了系统提供的线程库，此时CMakeLists.txt文件可以这样写：

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(app ${SRC_LIST})
target_link_libraries(app pthread calc)
```

在 CMake 中可以在生成可执行程序之前，通过命令指定出要链接的动态库的位置，指定静态库位置使用的也是这个命令：

``` cmake
link_directories(path)
```

所以修改之后的CMakeLists.txt文件应该是这样的：

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
file(GLOB SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
# 指定源文件或者动态库对应的头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 指定要链接的动态库的路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
# 添加并生成一个可执行程序
add_executable(app ${SRC_LIST})
# 指定要链接的动态库
target_link_libraries(app pthread calc)
```

通过link_directories指定了动态库的路径之后，在执行生成的可执行程序的时候，就不会出现找不到动态库的问题了。

> 温馨提示：使用 target_link_libraries 命令就可以链接动态库，也可以链接静态库文件。

## 日志

在CMake中可以用用户显示一条消息，该命令的名字为message：

```cmake
message([STATUS|WARNING|AUTHOR_WARNING|FATAL_ERROR|SEND_ERROR] "message to display" ...)
# - (无) ：重要消息
# - STATUS ：非重要消息
# - WARNING：CMake 警告, 会继续执行
# - AUTHOR_WARNING：CMake 警告 (dev), 会继续执行
# - SEND_ERROR：CMake 错误, 继续执行，但是会跳过生成的步骤
# - FATAL_ERROR：CMake 错误, 终止所有处理过程
```

CMake的命令行工具会在stdout上显示STATUS消息，在stderr上显示其他所有消息。CMake的GUI会在它的log区域显示所有消息。

CMake警告和错误消息的文本显示使用的是一种简单的标记语言。文本没有缩进，超过长度的行会回卷，段落之间以新行做为分隔符。

```cmake
# 输出一般日志信息
message(STATUS "source path: ${PROJECT_SOURCE_DIR}")
# 输出警告信息
message(WARNING "source path: ${PROJECT_SOURCE_DIR}")
# 输出错误信息
message(FATAL_ERROR "source path: ${PROJECT_SOURCE_DIR}")
```

## 变量操作

追加

有时候项目中的源文件并不一定都在同一个目录中，但是这些源文件最终却需要一起进行编译来生成最终的可执行文件或者库文件。如果我们通过 file 命令对各个目录下的源文件进行搜索，最后还需要做一个字符串拼接的操作，关于字符串拼接可以使用 set 命令也可以使用 list 命令

**使用 set 拼接**

如果使用set进行字符串拼接，对应的命令格式如下：

```cmake
# - set (name ${a} ${b} ...)
# 将后续文件都覆盖到 name 中
```

关于上面的命令其实就是将从第二个参数开始往后所有的字符串进行拼接，最后将结果存储到第一个参数中，如果第一个参数中原来有数据会对原数据就行覆盖。

**list 拼接**

如果使用list进行字符串拼接，对应的命令格式如下：

```cmake
# - list(APPEND <list> [<element> ...])
```

list 的功能比 set 要强大，字符串拼接只是它的其中一个功能，所以需要在它第一个参数的位置指定出我们要做的操作

```cmake
# - list(APPEND <list> <value> [<value> ...])
# - APPEND表示进行数据追加，后边的参数和set就一样了。
```

**字符串移除**

我们在通过file搜索某个目录就得到了该目录下所有的源文件，但是其中有些源文件并不是我们所需要的

```cmake
# - list(REMOVE_ITEM <list> <value> [<value> ...])
# - REMOVE_ITEM 表示进行数据追加，后边的参数和set就一样了。
```

通过上面的命令原型可以看到删除和追加数据类似。

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
set(TEMP "hello,world")
file(GLOB SRC_1 ${PROJECT_SOURCE_DIR}/*.cpp)
# 移除前日志
message(STATUS "message: ${SRC_1}")
# 移除 main.cpp
list(REMOVE_ITEM SRC_1 ${PROJECT_SOURCE_DIR}/main.cpp)
# 移除后日志
message(STATUS "message: ${SRC_1}")
```

> 在CMake中，使用set命令可以创建一个list。一个在list内部是一个由分号 ; 分割的一组字符串。

```cmake
set(tmp1 a;b;c;d;e)
set(tmp2 a b c d e)
message(${tmp1})
message(${tmp2})
# - 输出的结果:
# - abcde
# - abcde
# - set(var a b c d e)命令将会创建一个list:a;b;c;d;e
# - 但是最终打印变量值的时候得到的是abcde.
```



## list 其他功能

关于list命令还有其它功能，但是并不常用，在此就不一一进行举例介绍了

1、获取 list 的长度。

```cmake
# - list(LENGTH <list> <output variable>)

# - LENGTH：子命令LENGTH用于读取列表长度
# - <list>：当前操作的列表
# - <output variable>：新创建的变量，用于存储列表的长度。
```

2、读取列表中指定索引的的元素，可以指定多个索引

```cmake
# - list(GET <list> <element index> [<element index> ...] <output variable>)

# - <list>：当前操作的列表
# - <element index>：列表元素的索引
# - 从0开始编号，索引0的元素为列表中的第一个元素；
# - 索引也可以是负数，-1表示列表的最后一个元素，-2表示列表倒数第二个元素，以此类推
# - 当索引（不管是正还是负）超过列表的长度，运行会报错
# - <output variable>：新创建的变量，存储指定索引元素的返回结果，也是一个列表。
```

3、将列表中的元素用连接符（字符串）连接起来组成一个字符串

```cmake
# - list (JOIN <list> <glue> <output variable>)

# - <list>：当前操作的列表
# - <glue>：指定的连接符（字符串）
# - <output variable>：新创建的变量，存储返回的字符串
```

4、查找列表是否存在指定的元素，若果未找到，返回-1

```cmake
# - list(FIND <list> <value> <output variable>)

# - <list>：当前操作的列表
# - <value>：需要再列表中搜索的元素
# - <output variable>：新创建的变量
	# - 如果列表<list>中存在<value>，那么返回<value>在列表中的索引
	# - 如果未找到则返回-1。
```

5、将元素追加到列表中

```cmake
# - list (APPEND <list> [<element> ...])
```

6、在list中指定的位置插入若干元素

```cmake
# - list(INSERT <list> <element_index> <element> [<element> ...])
```

7、将元素插入到列表的0索引位置

```cmake
# - list (PREPEND <list> [<element> ...])
```

8、将列表中最后元素移除

```cmake
# - list (POP_BACK <list> [<out-var>...])
```

9、将列表中第一个元素移除

```cmake
# - list (POP_FRONT <list> [<out-var>...])
```

10、将指定的元素从列表中移除

```cmake
# - list (REMOVE_ITEM <list> <value> [<value> ...])
```

11、将指定索引的元素从列表中移除

``` cmake
# - list (REMOVE_AT <list> <index> [<index> ...])
```

12、移除列表中的重复元素

```cmake
# - list (REMOVE_DUPLICATES <list>)
```

13、列表翻转

```cmake
# - list (SORT <list> [COMPARE <compare>] [CASE <case>] [ORDER <order>])

# - COMPARE：指定排序方法。有如下几种值可选：
	# - STRING:按照字母顺序进行排序，为默认的排序方法
	# - FILE_BASENAME：如果是一系列路径名，会使用basename进行排序
	# - NATURAL：使用自然数顺序排序
# - CASE：指明是否大小写敏感。有如下几种值可选：
	# - SENSITIVE: 按照大小写敏感的方式进行排序，为默认值
	# - INSENSITIVE：按照大小写不敏感方式进行排序
# - ORDER：指明排序的顺序。有如下几种值可选：
	# - ASCENDING:按照升序排列，为默认值
	# - DESCENDING：按照降序排列

```



## 宏定义

在进行程序测试的时候，我们可以在代码中添加一些宏定义，通过这些宏来控制这些代码是否生效

在CMake中我们也可以做类似的事情，对应的命令叫做 add_definitions:

```cmake
# - add_definitions(-D宏名称)
```

针对于上面的源文件编写一个CMakeLists.txt，内容如下：

```cmake
cmake_minimum_required(VERSION 3.0)
project(TEST)
# 自定义 DEBUG 宏
add_definitions(-DDEBUG)
add_executable(app ./test.c)
```

```cpp
#include <iostream>

int main () {
    int a = 0;

#ifdef DEBUG
    std::cout << "not bug\n";
#endif
    return 0;
}
```

通过这种方式，上述代码中的第八行日志就能够被输出出来了。

## 预定义宏

下面的列表中为一些CMake中常用的宏：

| 宏                       | 功能                                                         |
| ------------------------ | ------------------------------------------------------------ |
| PROJECT_SOURCE_DIR       | 使用cmake命令后紧跟的目录，一般是工程的根目录                |
| PROJECT_BINARY_DIR       | 执行cmake命令的目录                                          |
| CMAKE_CURRENT_SOURCE_DIR | 当前处理的CMakeLists.txt所在的路径                           |
| CMAKE_CURRENT_BINARY_DIR | target 编译目录                                              |
| EXECUTABLE_OUTPUT_PATH   | 重新定义目标二进制可执行文件的存放位置                       |
| LIBRARY_OUTPUT_PATH      | 重新定义目标链接库文件的存放位置                             |
| PROJECT_NAME             | 返回通过PROJECT指令定义的项目名称                            |
| CMAKE_BINARY_DIR         | 项目实际构建路径，假设在build目录进行的构建，那么得到的就是这个目录的路径 |

## 嵌套 CMake





根目录的 CMake

```cmake
# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(demo)
# 语言版本
set(CMAKE_CXX_STANDARD 17)

# 定义变量
# 静态库生成的路径
set(LIBPATH ${PROJECT_SOURCE_DIR}/lib)
# 可执行程序存储目录
set(EXEPATH ${PROJECT_SOURCE_DIR}/bin)
# 头文件路径
set(HEAD_PATH ${PROJECT_SOURCE_DIR}/include)

# 库文件的name
set(CALCLIB calc)
set(SORTLIB sort)

# 可执行程序的名字
set(APPNAME1 app1)
set(APPNAME2 app2)

# 给当前节点添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)
```

calc 子目录的 CMake

```cmake
# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(calc)

# 搜索源文件
aux_source_directory(./ SRC)
# 链接头文件
include_directories(${HEAD_PATH})

set(LIBRARY_OUTPUT_PATH ${LIBPATH})
# 构造静态库
add_library(${CALCLIB} STATIC ${SRC})
```

test1 子目录的 CMake

```cmake
# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(test1)

# 搜索 .cpp 文件
aux_source_directory(./ SRC)
# 链接头文件
include_directories(${HEAD_PATH})

# 链接静态库
link_directories(${LIBPATH})
link_libraries(${CALCLIB})

# 创建可执行文件
set(EXECUTABLE_OUTPUT_PATH ${EXEPATH})
add_executable(${APPNAME1} ${SRC})
```

构建项目

进入跟节点目录的 build 中，执行 cmake .. 





## part8 案例

文件预览

```toml
part8
├── CMakeLists.txt
├── calc
│   ├── CMakeLists.txt
│   ├── add.cpp
│   ├── dif.cpp
│   ├── mult.cpp
│   └── sub.cpp
├── include
│   ├── calc.h
│   └── sort.h
├── sort
│   ├── CMakeLists.txt
│   ├── insert.cpp
│   └── select.cpp
└── test1
    ├── CMakeLists.txt
    └── main.cpp
```

根目录

```cmake
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
```

calc 子目录

```cmake
# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(calc)

# 搜索源文件
aux_source_directory(./ SRC)
# 链接头文件
include_directories(${HEAD_PATH})
# 动态库生成位置
set(LIBRARY_OUTPUT_PATH ${DLL_PATH})
# 构造动态库 (SHARED)
add_library(${CALC_NAME} SHARED ${SRC})
```

sort 子目录

```cmake
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
```

test1 子目录

```cmake
# CMake 最低版本
cmake_minimum_required(VERSION 3.15)
# 项目名称
project(test1)

# 搜索 .cpp 文件
aux_source_directory(./ SRC)
# 链接头文件
include_directories(${HEAD_PATH})

# 链接静态库
link_directories(${LIB_PATH})
link_libraries(${SORT_NAME})

# 创建可执行文件
set(EXECUTABLE_OUTPUT_PATH ${EXE_PATH})
add_executable(${APP_NAME} ${SRC})
```

构建完成

```shell
Scanning dependencies of target calc
[ 10%] Building CXX object calc/CMakeFiles/calc.dir/add.cpp.o
[ 20%] Building CXX object calc/CMakeFiles/calc.dir/dif.cpp.o
[ 30%] Building CXX object calc/CMakeFiles/calc.dir/mult.cpp.o
[ 40%] Building CXX object calc/CMakeFiles/calc.dir/sub.cpp.o
[ 50%] Linking CXX shared library ../../dll/libcalc.so
[ 50%] Built target calc
Scanning dependencies of target sort
[ 60%] Building CXX object sort/CMakeFiles/sort.dir/insert.cpp.o
[ 70%] Building CXX object sort/CMakeFiles/sort.dir/select.cpp.o
[ 80%] Linking CXX static library ../../lib/libsort.a
[ 80%] Built target sort
Scanning dependencies of target app
[ 90%] Building CXX object test1/CMakeFiles/app.dir/main.cpp.o
[100%] Linking CXX executable ../../bin/app
[100%] Built target app
```



