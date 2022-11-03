cmake_minimum_required(VERSION 2.8)

project(sylar)

include (cmake/utils.cmake)

#显示详细的原始编译信息，主要用于定位一些链接错误，看看库路径什么的是否配置对
set(CMAKE_VERBOSE_MAKEFILE ON)

#C++ 编译标志相关变量。
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -pthread -rdynamic -O0 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

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
${PROJECT_SOURCE_DIR}/sylar/fiber.cc
)

#添加要生成的库文件
add_library(sylar SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(sylar)

# set_target_properties(sylar PROPERTIES OUTPUT_NAME "sylar")
# add_library(sylar_static STATIC $(LIB_SRC))
# SET_TARGET_PROPERTIES (sylar_static PROPERTIES OUTPUT_NAME "sylar")

add_executable(test tests/test.cc)
add_dependencies(test sylar)
force_redefine_file_macro_for_sources(test)
target_link_libraries(test sylar yaml-cpp)

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config sylar)
force_redefine_file_macro_for_sources(test_config)
target_link_libraries(test_config sylar yaml-cpp)


add_executable(test_thread tests/test_thread.cc)
add_dependencies(test_thread sylar)
force_redefine_file_macro_for_sources(test_thread)
target_link_libraries(test_thread sylar yaml-cpp)

add_executable(test_assert tests/test_assert.cc)
add_dependencies(test_assert sylar)
force_redefine_file_macro_for_sources(test_assert)
target_link_libraries(test_assert sylar yaml-cpp)

add_executable(test_fiber tests/test_fiber.cc)
add_dependencies(test_fiber sylar)
force_redefine_file_macro_for_sources(test_fiber)
target_link_libraries(test_fiber sylar yaml-cpp)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)