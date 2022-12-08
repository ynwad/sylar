/*
 * @Author: Ynwad_
 * @Date: 2022-12-08 22:52:06
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-12-09 00:13:26
 * @FilePath: /sylar/tests/test_http_server.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/http/http_server.h"
#include "sylar/log.h"
// #include "sylar/hook.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

#define XX(...) #__VA_ARGS__


// sylar::IOManager::ptr worker;
void run() {
    g_logger->setLevel(sylar::LogLevel::INFO);
    //sylar::http::HttpServer::ptr server(new sylar::http::HttpServer(true, worker.get(), sylar::IOManager::GetThis()));
    sylar::http::HttpServer::ptr server(new sylar::http::HttpServer(false));
    sylar::Address::ptr addr = sylar::Address::LookupAnyIPAddress("172.19.177.186:8020");
    while(!server->bind(addr)) {
        sleep(2);
    }

    server->start();
}

int main(int argc, char** argv) {
    // sylar::set_hook_enable(true);
    sylar::IOManager iom(2, true, "main");
    // worker.reset(new sylar::IOManager(3, false, "worker"));
    iom.schedule(run);
    return 0;
}
