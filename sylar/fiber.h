/*
 * @Author: Ynwad_
 * @Date: 2022-10-28 00:46:06
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-11-17 22:47:45
 * @FilePath: /sylar/sylar/fiber.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#ifndef __SYLAR_FIBER_H__
#define __SYLAR_FIBER_H__

#include <memory>
#include <functional>
#include <ucontext.h>
#include "thread.h"

namespace sylar{

class Fiber : public std::enable_shared_from_this<Fiber>{
    friend class Scheduler;
public:
    typedef std::shared_ptr<Fiber> ptr;

    enum State{
        INIT,
        HOLD,
        EXEC,
        TERM,
        READY,
        EXCPT
    };

private:
    Fiber();

public:
    Fiber(std::function<void()> cb, size_t stackSize = 0, bool use_caller = false);
    ~Fiber();

    //重置协程函数，并重置状态
    //INIT, TERM
    void reset(std::function<void()> cb);

    //切换到当前协程执行
    void swapIn();

    //切换到后台执行
    void swapOut();

    /**
     * @brief 将当前线程切换到执行状态
     * @pre 执行的为当前线程的主协程
     */
    void call();

    /**
     * @brief 将当前线程切换到后台
     * @pre 执行的为该协程
     * @post 返回到线程的主协程
     */
    void back();

    /**
     * @brief 协程执行函数
     * @post 执行完成返回到线程调度协程
     */
    static void CallerMainFunc();

    /**
     * @description: 执行完，返回到线程主协程
     * @return {*}
     */    
    static void MainFunc();

    uint64_t getId() const;

    /**
     * @brief 返回协程状态
     */
    State getState() const { return m_state;}
public:
    //设置当前协程
    static void SetThis(Fiber* f);

    //返回当前协程
    static Fiber::ptr GetThis();

    //协程切换到后台，并设置为Ready状态
    static void YieldToReady();

    //协程切换到后台，并设置为Hold状态
    static void YieldToHold();

    //总协程数
    static uint64_t TotalFibers();

    static uint64_t GetFiberId();

private:
    uint64_t m_id  = 0;
    uint32_t m_statckSize = 0;
    State m_state = INIT;

    ucontext_t m_ctx;
    void* m_stack = nullptr;
    std::function<void()> m_cb;
};

}
#endif