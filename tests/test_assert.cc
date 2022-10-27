/*
 * @Author: Ynwad_
 * @Date: 2022-10-27 01:14:24
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-10-27 01:27:04
 * @FilePath: /sylar/tests/test_assert.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/sylar.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test_assert(){
    SYLAR_LOG_INFO(g_logger) << sylar::BackTraceToString(10);
    assert(0);
}

int main(int argc, char** argv){
    
    test_assert();
    return 0;
}