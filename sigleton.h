<<<<<<< HEAD
/*
 * @Author: git config user.name
 * @Date: 2022-06-16 04:44:59
 * @LastEditors: git config user.name && git config user.email
 * @LastEditTime: 2022-06-16 04:55:01
 * @FilePath: /sylar/sigleton.h
 * @Description: 
 * 
 * Copyright (c) 2022 by ${git_name_email}, All Rights Reserved. 
 */


=======
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c
/**
 * @file singleton.h
 * @brief 单例模式封装
 * @author sylar.yin
 * @email 564628276@qq.com
 * @date 2019-05-18
 * @copyright Copyright (c) 2019年 sylar.yin All rights reserved (www.sylar.top)
 */
<<<<<<< HEAD

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
#ifndef __SYLAR_SINGLETON_H__
#define __SYLAR_SINGLETON_H__

#include <memory>

namespace sylar {
=======
#ifndef __YNWAD_SINGLETON_H__
#define __YNWAD_SINGLETON_H__

#include <memory>

namespace ynwad {
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c

namespace {

template<class T, class X, int N>
T& GetInstanceX() {
    static T v;
    return v;
}

template<class T, class X, int N>
std::shared_ptr<T> GetInstancePtr() {
    static std::shared_ptr<T> v(new T);
    return v;
}

}
<<<<<<< HEAD

/**
 * @brief 单例模式封装类
 * @details T 类型
 *          X 为了创造多个实例对应的Tag
 *          N 同一个Tag创造多个实例索引
 */
template<class T, class X = void, int N = 0>
class Sigleton {
public:
    /**
     * @brief 返回单例裸指针
     */
    static T* GetInstance() {
        static T v;
        return &v;
        //return &GetInstanceX<T, X, N>();
    }
};

/**
 * @brief 单例模式智能指针封装类
 * @details T 类型
 *          X 为了创造多个实例对应的Tag
 *          N 同一个Tag创造多个实例索引
 */
template<class T, class X = void, int N = 0>
class SingletonPtr {
public:
    /**
     * @brief 返回单例智能指针
     */
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> v(new T);
        return v;
        //return GetInstancePtr<T, X, N>();
    }
};

}

#endif
=======
}
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c
