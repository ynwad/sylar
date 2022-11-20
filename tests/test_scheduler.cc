/*
 * @Author: Ynwad_
 * @Date: 2022-11-16 01:19:35
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-11-18 01:29:42
 * @FilePath: /sylar/tests/test_scheduler.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/sylar.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_fiber() {
    static int s_count = 10;
    SYLAR_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;

    sleep(1);
    if(--s_count >= 0) {
        sylar::Scheduler::GetThis()->schedule(&test_fiber, -1);
    }
}

int main(int argc, char** argv) {
    SYLAR_LOG_INFO(g_logger) << "main";
    sylar::Scheduler sc(2, true, "test");
    sc.start();
    SYLAR_LOG_INFO(g_logger) << "**************************************************";
    sleep(2);
    SYLAR_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    // sleep(10);
    SYLAR_LOG_INFO(g_logger) << "--------------------------------------------------";

    sc.stop();

    SYLAR_LOG_INFO(g_logger) << "over";
    return 0;
}
