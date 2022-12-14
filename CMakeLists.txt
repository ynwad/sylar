cmake_minimum_required(VERSION 2.8)

project(sylar)

#显示详细的原始编译信息，主要用于定位一些链接错误，看看库路径什么的是否配置对
set(CMAKE_VERBOSE_MAKEFILE ON)

#C++ 编译标志相关变量。
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -pthread -rdynamic -O0 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)
include_directories(/usr/local/include)

link_directories(/usr/local/lib)

#设置变量
set(LIB_SRC
${PROJECT_SOURCE_DIR}/sylar/log.cc
${PROJECT_SOURCE_DIR}/sylar/utils.cc

${PROJECT_SOURCE_DIR}/sylar/thread.cc
${PROJECT_SOURCE_DIR}/sylar/utils.cc
${PROJECT_SOURCE_DIR}/sylar/mutex.cc
${PROJECT_SOURCE_DIR}/sylar/config.cc
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

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)