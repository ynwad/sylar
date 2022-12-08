/*
 * @Author: Ynwad_
 * @Date: 2022-08-24 23:05:37
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-12-07 21:24:59
 * @FilePath: /sylar/sylar/utils.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#ifndef __SYLAR_UTIL_H__
#define __SYLAR_UTIL_H__

#include <cxxabi.h>
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <sys/syscall.h>

namespace sylar {

/**
 * @brief 返回当前线程的ID
 */
pid_t GetThreadId();

/**
 * @brief 返回当前协程的ID
 */
uint64_t GetFiberId();

/**
 * @description: 获取当前调用栈信息
 * @param {std::vector<std::string>&} bt 保存调用栈 
 * @param {int} size 最多返回的层数
 * @param {int} nskip  跳过栈顶的层数
 * @return {*} void
 */
void BackTrace(std::vector<std::string>& bt, int size = 64, int nskip = 1);

/**
 * @description: 
 * @param {int} size    最多返回的层数
 * @param {int} skip    跳过栈顶的层数
 * @param {string&} prefix
 * @return {std::string} 返回转化为字符串的堆栈信息
 */
std::string BackTraceToString(int size = 64, int skip = 2, const std::string& prefix = "");

/**
 * @brief 获取当前时间的毫秒
 */
uint64_t GetCurrentMS();

/**
 * @brief 获取当前时间的微秒
 */
uint64_t GetCurrentUS();

std::string ToUpper(const std::string& name);

std::string ToLower(const std::string& name);

std::string Time2Str(time_t ts = time(0), const std::string& format = "%Y-%m-%d %H:%M:%S");
time_t Str2Time(const char* str, const char* format = "%Y-%m-%d %H:%M:%S");

class FSUtil {
public:
    static void ListAllFile(std::vector<std::string>& files
                            ,const std::string& path
                            ,const std::string& subfix);
    static bool Mkdir(const std::string& dirname);
    static bool IsRunningPidfile(const std::string& pidfile);
    static bool Rm(const std::string& path);
    static bool Mv(const std::string& from, const std::string& to);
    static bool Realpath(const std::string& path, std::string& rpath);
    static bool Symlink(const std::string& frm, const std::string& to);
    static bool Unlink(const std::string& filename, bool exist = false);
    static std::string Dirname(const std::string& filename);
    static std::string Basename(const std::string& filename);
    static bool OpenForRead(std::ifstream& ifs, const std::string& filename
                    ,std::ios_base::openmode mode);
    static bool OpenForWrite(std::ofstream& ofs, const std::string& filename
                    ,std::ios_base::openmode mode);
};


class StringUtil {
public:
    static std::string Format(const char* fmt, ...);
    static std::string Formatv(const char* fmt, va_list ap);

    static std::string UrlEncode(const std::string& str, bool space_as_plus = true);
    static std::string UrlDecode(const std::string& str, bool space_as_plus = true);

    static std::string Trim(const std::string& str, const std::string& delimit = " \t\r\n");
    static std::string TrimLeft(const std::string& str, const std::string& delimit = " \t\r\n");
    static std::string TrimRight(const std::string& str, const std::string& delimit = " \t\r\n");


    static std::string WStringToString(const std::wstring& ws);
    static std::wstring StringToWString(const std::string& s);

};


}

#endif