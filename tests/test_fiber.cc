/*
 * @Author: Ynwad_
 * @Date: 2022-11-02 00:23:31
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-11-02 01:02:15
 * @FilePath: /sylar/tests/test_fiber.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/sylar.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run_in_fiber(){
    SYLAR_LOG_INFO(g_logger) << "run_in_fiber begin";
    sylar::Fiber::GetThis()->YieldToHold();
    SYLAR_LOG_INFO(g_logger) << "run_in_fiber end";
}

int main(int argc, char** argv){
    sylar::Fiber::GetThis();
    SYLAR_LOG_INFO(g_logger) << "main_begin:";
    sylar::Fiber::ptr fiber(new sylar::Fiber(run_in_fiber));
    fiber->swapIn();
    SYLAR_LOG_INFO(g_logger) << "main after swapIn";
    fiber->swapIn();
    SYLAR_LOG_INFO(g_logger) << "main after end";
    return 0;
}

