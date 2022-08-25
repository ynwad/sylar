/*
 * @Author: error: git config user.name & please set dead value or install git
 * @Date: 2022-08-03 00:51:01
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-08-03 00:53:16
 * @FilePath: /ynwad/mutex.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by error: git config user.name && git config user.email & please set dead value or install git, All Rights Reserved. 
 */
#include "mutex.h"
// #include "macro.h"
// #include "scheduler.h"

namespace sylar {

Semaphore::Semaphore(uint32_t count) {
    if(sem_init(&m_semaphore, 0, count)) {
        // throw std::logic_error("sem_init error");
    }
}

Semaphore::~Semaphore() {
    sem_destroy(&m_semaphore);
}

void Semaphore::wait() {
    if(sem_wait(&m_semaphore)) {
        // throw std::logic_error("sem_wait error");
    }
}

void Semaphore::notify() {
    if(sem_post(&m_semaphore)) {
        // throw std::logic_error("sem_post error");
    }
}



}
