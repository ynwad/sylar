/*
 * @Author: Ynwad_
 * @Date: 2022-12-05 21:09:08
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-12-05 22:32:15
 * @FilePath: /sylar/tests/test_address.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/address.h"
#include "sylar/log.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test() {
    std::vector<sylar::Address::ptr> addrs;

    SYLAR_LOG_INFO(g_logger) << "begin";
    // bool v = sylar::Address::Lookup(addrs, "localhost:3080");
    // bool v = sylar::Address::Lookup(addrs, "www.baidu.com", AF_INET);
    bool v = sylar::Address::Lookup(addrs, "www.bing.com:443", AF_INET, SOCK_STREAM);
    SYLAR_LOG_INFO(g_logger) << "end";
    if(!v) {
        SYLAR_LOG_ERROR(g_logger) << "lookup fail";
        return;
    }

    for(size_t i = 0; i < addrs.size(); ++i) {
        SYLAR_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
    }

    auto addr = sylar::Address::LookupAny("localhost:4080");
    if(addr) {
        SYLAR_LOG_INFO(g_logger) << *addr;
    } else {
        SYLAR_LOG_ERROR(g_logger) << "error";
    }
}

void test_iface() {
    std::multimap<std::string, std::pair<sylar::Address::ptr, uint32_t> > results;

    bool v = sylar::Address::GetInterfaceAddresses(results, AF_INET6);
    if(!v) {
        SYLAR_LOG_ERROR(g_logger) << "GetInterfaceAddresses fail";
        return;
    }

    for(auto& i: results) {
        SYLAR_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() << " - "
            << i.second.second;
    }
}

void test_ipv4() {
    auto addr = sylar::IPAddress::Create("127.0.0.1", 1080);
    // auto addr = sylar::IPAddress::Create("127.0.0.8", 1);
    if(addr) {
        SYLAR_LOG_INFO(g_logger) << addr->toString();
    }
}

int main(int argc, char** argv) {
    // test_ipv4();
    test_iface();
    // test();
    return 0;
}
