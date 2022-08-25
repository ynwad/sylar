/*
 * @Author: Ynwad_
 * @Date: 2022-08-24 22:44:38
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-08-26 01:09:30
 * @FilePath: /sylar/tests/test.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "sylar/log.h"
#include "sylar/utils.h"

using namespace sylar;

const std::string str = "namemmmmmmm";

int main()
{
    std::shared_ptr<Logger> logger = std::make_shared<Logger>();

    StdOutLogAppender::ptr stdappender(new StdOutLogAppender);
    LogFormatter::ptr fmt(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));
    stdappender->setFormatter(fmt);
    stdappender->setLevel(LogLevel::ERROR);

    FileLogAppender::ptr file_appender(new FileLogAppender("./log.txt"));
    LogFormatter::ptr fmt2(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));
    file_appender->setFormatter(fmt2);

    file_appender->setLevel(LogLevel::INFO);

    logger->addAppender(stdappender);
    logger->addAppender(file_appender);
    std::string ss = "123456677";
    SYLAR_LOG_LEVEL(logger, LogLevel::FATAL)<<"222222222222222222222222222222"<<"  "<<ss;

    // std::shared_ptr<LogEvent> pEvent = std::make_shared<LogEvent>();
    // pEvent->getLogger()->log(logger, );
    auto l = sylar::LoggerMgr::GetInstance()->getLogger("xxxx");
    l->addAppender(file_appender);
    l->setLevel(sylar::LogLevel::ERROR);
    SYLAR_LOG_ERROR(l)<<"xx";
}