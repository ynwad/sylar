/**
 * @file util.h
 * @brief 常用的工具函数
<<<<<<< HEAD
 * @author sylar.yin
=======
 * @author ynwad.yin
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c
 * @email qingchenchn@gmail.com
 * @date 2022-6-24
 */

<<<<<<< HEAD
#ifndef __SYLAR_UTIL_H__
#define __SYLAR_UTIL_H__
=======
#ifndef __YNWAD_UTIL_H__
#define __YNWAD_UTIL_H__
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c

#include <iostream>
#include <vector>
#include <string>
#include <iostream>
<<<<<<< HEAD
#include <sys/syscall.h>

namespace sylar {
=======

namespace ynwad {
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c
/**
 * @brief 返回当前线程的ID
 */
pid_t GetThreadId();

/**
 * @brief 返回当前协程的ID
 */
uint32_t GetFiberId();

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

}




#endif