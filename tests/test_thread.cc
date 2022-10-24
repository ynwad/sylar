/*
 * @Author: Ynwad_
 * @Date: 2022-09-26 22:37:29
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-10-19 00:46:51
 * @FilePath: /sylar/tests/test_thread.cc
 * @Description: Thread Wrap
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/sylar.h"
#include <unistd.h>

sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

static int count = 0;
sylar::RWMutex s_mutex;

void fun1(){
    SYLAR_LOG_INFO(g_logger) << "name: " << sylar::Thread::GetName()
                             << " this.name: " << sylar::Thread::GetThis()->getName()
                             << " id: " << sylar::GetThreadId()
                             << " this.id: " << sylar::Thread::GetThis()->getId();

    for(int i = 0; i < 100000; ++i) {
        sylar::RWMutex::WriteLock lock(s_mutex);
        // sylar::Mutex::Lock lock(s_mutex);
        ++count;
    }
}

void fun2() {
    while(true) {
        SYLAR_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    }
}

void fun3() {
    while(true) {
        SYLAR_LOG_INFO(g_logger) << "========================================";
    }
}

int main(int argc, char** argv){
    SYLAR_LOG_INFO(g_logger) << "thread test begin()";
    YAML::Node root = YAML::LoadFile("/home/ynwad/workspace/sylar/bin/conf/log.yaml");
    // std::cout << sylar::LoggerMgr::GetInstance()->toYamlString() << std::endl;

    sylar::Config::LoadFromYaml(root);
    // std::cout << "=============" << std::endl;
    // std::cout << sylar::LoggerMgr::GetInstance()->toYamlString() << std::endl;

    std::vector<sylar::Thread::ptr> thrs;
    for(int i = 0; i < 2; ++i) {
        sylar::Thread::ptr thr(new sylar::Thread(&fun2, "name_" + std::to_string(i * 2)));
        sylar::Thread::ptr thr2(new sylar::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        //sylar::Thread::ptr thr2(new sylar::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        thrs.push_back(thr2);
        //thrs.push_back(thr2);
    }

    for(size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }

    // SYLAR_LOG_INFO(g_logger) << "thread test end";
    // SYLAR_LOG_INFO(g_logger) << "count=" << count;

    // SYLAR_LOG_ERROR(g_logger) << "thread test end()";
    std::cout << sylar::LoggerMgr::GetInstance()->toYamlString() << std::endl;
    std::cout << count << std::endl;
    return 0;
}