/*
 * @Author: error: git config user.name & please set dead value or install git
 * @Date: 2022-08-05 22:20:10
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-24 21:10:43
 * @FilePath: /ynwad/config.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include "config.h"

namespace sylar{
    static sylar::logger::ptr g_logger = SYLAR_LOG_NAME("system");
    Config::ConfigVarMap Config::s_datas;
}
