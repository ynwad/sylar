/*
 * @Author: Ynwad_
 * @Date: 2022-12-08 00:53:31
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-12-08 23:04:21
 * @FilePath: /sylar/tests/test_tcp_server.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/tcp_server.h"
#include "sylar/iomanager.h"
#include "sylar/log.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run() {
    auto addr = sylar::Address::LookupAny("172.19.177.186:8020");
    //auto addr2 = sylar::UnixAddress::ptr(new sylar::UnixAddress("/tmp/unix_addr"));
    std::vector<sylar::Address::ptr> addrs;
    addrs.push_back(addr);
    //addrs.push_back(addr2);

    sylar::TcpServer::ptr tcp_server(new sylar::TcpServer);
    std::vector<sylar::Address::ptr> fails;
    while(!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
    
}
int main(int argc, char** argv) {
    sylar::IOManager iom(2);
    iom.schedule(run);
    return 0;
}
