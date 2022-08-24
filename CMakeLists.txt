cmake_minimum_required(VERSION 2.8)
<<<<<<< HEAD
project(sylar)
=======
project(ynwad)
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c

#显示详细的原始编译信息，主要用于定位一些链接错误，看看库路径什么的是否配置对
set(CMAKE_VERBOSE_MAKEFILE ON)

#C++ 编译标志相关变量。
<<<<<<< HEAD
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -pthread -rdynamic -O0 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(/usr/local/include)

link_directories(/usr/local/lib)
=======
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -pthread -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c
#设置变量
set(LIB_SRC
${PROJECT_SOURCE_DIR}/log.cc
${PROJECT_SOURCE_DIR}/utils.cc
<<<<<<< HEAD
${PROJECT_SOURCE_DIR}/thread.cc
${PROJECT_SOURCE_DIR}/utils.cc
${PROJECT_SOURCE_DIR}/mutex.cc
${PROJECT_SOURCE_DIR}/config.cc
    )

#添加要生成的库文件
add_library(sylar SHARED ${LIB_SRC})
# set_target_properties(sylar PROPERTIES OUTPUT_NAME "sylar")
# add_library(sylar_static STATIC $(LIB_SRC))
# SET_TARGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")

add_executable(test tests/test.cc)
add_dependencies(test sylar)
target_link_libraries(test sylar)

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config sylar)
target_link_libraries(test_config sylar yaml-cpp)
=======
    )

#添加要生成的库文件
add_library(ynwad SHARED ${LIB_SRC})
# set_target_properties(ynwad PROPERTIES OUTPUT_NAME "ynwad")
# add_library(ynwad_static STATIC $(LIB_SRC))
# SET_TARGET_PROPERTIES (ynwad_static PROPERTIES OUTPUT_NAME "ynwad")

add_executable(test tests/test.cc)
add_dependencies(test ynwad)
target_link_libraries(test ynwad)
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)