/*
 * @Author: Ynwad_
 * @Date: 2022-11-02 00:23:31
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-11-17 22:39:30
 * @FilePath: /sylar/tests/test_fiber.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/sylar.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run_in_fiber(){
    SYLAR_LOG_INFO(g_logger) << "run_in_fiber begin";
    sylar::Fiber::YieldToHold();
    SYLAR_LOG_INFO(g_logger) << "run_in_fiber end";
}

void test_fiber(){
    SYLAR_LOG_INFO(g_logger) << "main begin -1";
    {
        sylar::Fiber::GetThis();
        SYLAR_LOG_INFO(g_logger) << "main_begin:";
        sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));
        SYLAR_LOG_INFO(g_logger) << "main after swapIn";
        fiber->call();
        SYLAR_LOG_INFO(g_logger) << "main after end";
        // fiber->swapIn();
    }

    SYLAR_LOG_INFO(g_logger) << "main after -1";
}

int main(int argc, char** argv){
    sylar::Thread::SetName("main");

    std::vector<sylar::Thread::ptr> thrs;
    for(int i = 0; i < 1; ++i){
        thrs.emplace_back(sylar::Thread::ptr(new sylar::Thread(test_fiber, 
                        "Thread_name_" + std::to_string(i))));
    }

    for(int i = 0; i < 1;++i){
        thrs[i]->join();
    }
    return 0;
}

