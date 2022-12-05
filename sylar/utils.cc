/*
 * @Author: Ynwad_
 * @Date: 2022-08-24 22:44:28
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-12-05 23:07:50
 * @FilePath: /sylar/sylar/utils.cc
 * @Description: 常用的一些函数
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */

#include "utils.h"
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <execinfo.h>
#include "log.h"
#include "fiber.h"

namespace sylar{

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

pid_t GetThreadId() {
    return syscall(SYS_gettid);
}

uint64_t GetFiberId() {
    return sylar::Fiber::GetFiberId();
}

/**
 * @description: 用于将backtrace_symbols函数所返回的字符串解析成对应的函数名，便于理解
 * @param {char*} str
 * @return {*}
 */
static std::string demangle(const char* str){
    size_t size = 0;
    int status = 0;
    std::string rt;
    rt.resize(256);
    if(1 == sscanf(str, "%*[^(]%*[^_]%255[^)+]", &rt[0])){
        char* v = abi::__cxa_demangle(&rt[0], nullptr, &size, &status);
        if(v){
            std::string result(v);
            free(v);
            return result;
        }
    }
    if(1 == sscanf(str, "%255s", &rt[0])){
        return rt;
    }
    return str;
}

void BackTrace(std::vector<std::string>& bt, int size, int nskip){
    void** array = (void**)malloc((sizeof(void*) * size));
    size_t s = ::backtrace(array, size);

    char** strings = backtrace_symbols(array, s);
    if(strings == nullptr){
        SYLAR_LOG_ERROR(g_logger) << "backtrace_symbols error";
        return;
    }

    for(size_t i = nskip; i < s; ++i){
        bt.emplace_back(demangle(strings[i]));
        // bt.emplace_back(strings[i]);
    }

    free(strings);
    free(array);
}

std::string BackTraceToString(int size, int skip, const std::string& prefix){
    std::vector<std::string> bt;
    BackTrace(bt, size, skip);
    std::stringstream ss;
    for(size_t i = 0; i < bt.size(); ++i){
        ss << prefix << bt[i] << std::endl;
    }
    return ss.str();
}


uint64_t GetCurrentMS(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000ul  + tv.tv_usec / 1000;
}

uint64_t GetCurrentUS(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 * 1000ul  + tv.tv_usec;
}

static int __lstat(const char* file, struct stat* st = nullptr) {
    struct stat lst;
    int ret = lstat(file, &lst);
    if(st) {
        *st = lst;
    }
    return ret;
}

static int __mkdir(const char* dirname) {
    if(access(dirname, F_OK) == 0) {
        return 0;
    }
    return mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

bool FSUtil::Mkdir(const std::string& dirname) {
    if(__lstat(dirname.c_str()) == 0) {
        return true;
    }
    //strdup()，复制string，返回char*
    char* path = strdup(dirname.c_str());

    //搜索‘/’在字符串中第一次出现的位置
    char* ptr = strchr(path + 1, '/');
    do {
        for(; ptr; *ptr = '/', ptr = strchr(ptr + 1, '/')) {
            *ptr = '\0';
            if(__mkdir(path) != 0) {
                break;
            }
        }
        if(ptr != nullptr) {
            break;
        } else if(__mkdir(path) != 0) {
            break;
        }
        free(path);
        return true;
    } while(0);
    free(path);
    return false;
}

bool FSUtil::OpenForWrite(std::ofstream& ofs, const std::string& filename
                        ,std::ios_base::openmode mode) {
    ofs.open(filename.c_str(), mode);   
    if(!ofs.is_open()) {
        std::string dir = Dirname(filename);
        Mkdir(dir);
        ofs.open(filename.c_str(), mode);
    }
    return ofs.is_open();
}

std::string FSUtil::Dirname(const std::string& filename){
    if(filename.empty()) {
        return ".";
    }
    auto pos = filename.rfind('/');
    if(pos == 0) {
        return "/";
    } else if(pos == std::string::npos) {
        return ".";
    } else {
        return filename.substr(0, pos);
    }
}


bool FSUtil::Unlink(const std::string& filename, bool exist) {
    if(!exist && __lstat(filename.c_str())) {
        return true;
    }
    return ::unlink(filename.c_str()) == 0;
}

}