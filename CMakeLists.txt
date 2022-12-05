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

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

#设置变量
set(LIB_SRC
    sylar/log.cc
    sylar/utils.cc

    sylar/thread.cc
    sylar/utils.cc
    sylar/mutex.cc
    sylar/config.cc
    sylar/fiber.cc
    sylar/scheduler.cc
    sylar/iomanager.cc
    sylar/timer.cc
    sylar/hook.cc
    sylar/address.cc
    sylar/fd_manager.cc
    sylar/socket.cc
)

#添加要生成的库文件
add_library(sylar SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(sylar)

find_library(PTHREAD pthread)

set(LIBS
        sylar
        dl
        pthread
        yaml-cpp
        # jsoncpp
        # ${ZLIB_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        # ${PROTOBUF_LIBRARIES}
        # event
        # hiredis_vip
        # mysqlclient_r
        # zookeeper_mt
        # sqlite3
        # tinyxml2
        # jemalloc
        )

sylar_add_executable(test_config "tests/test_config.cc" sylar "${LIBS}")
sylar_add_executable(test_thread "tests/test_thread.cc" sylar "${LIBS}")
sylar_add_executable(test_fiber "tests/test_fiber.cc" sylar "${LIBS}")
sylar_add_executable(test_scheduler "tests/test_scheduler.cc" sylar "${LIBS}")
sylar_add_executable(test_iomanager "tests/test_iomanager.cc" sylar "${LIBS}")
sylar_add_executable(test_hook "tests/test_hook.cc" sylar "${LIBS}")
sylar_add_executable(test_address "tests/test_address.cc" sylar "${LIBS}")
sylar_add_executable(test_socket "tests/test_socket.cc" sylar "${LIBS}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)