/*
 * @Author: error: git config user.name & please set dead value or install git
 * @Date: 2022-08-05 22:20:10
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-08-24 23:33:10
 * @FilePath: /sylar/config.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include "config.h"
#include "log.h"

namespace sylar{
    static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");
    Config::ConfigVarMap Config::s_datas;
}
