/*
 * @Author: Ynwad_
 * @Date: 2022-11-15 23:28:37
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-11-16 01:22:39
 * @FilePath: /sylar/sylar/scheduler.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#ifndef __SYLAR_SCHEDULER_H__
#define __SYLAR_SCHEDULER_H__

#include <memory>
#include <vector>
#include <list>
#include <iostream>
#include "fiber.h"
#include "thread.h"

namespace sylar{


struct FiberAndThread {
    /// 协程
    Fiber::ptr fiber;
    /// 协程执行函数
    std::function<void()> cb;
    /// 线程id
    int thread;

    /**
     * @brief 构造函数
     * @param[in] f 协程
     * @param[in] thr 线程id
     */
    FiberAndThread(Fiber::ptr f, int thr)
        :fiber(f), thread(thr) {
    }

    /**
     * @brief 构造函数
     * @param[in] f 协程指针
     * @param[in] thr 线程id
     * @post *f = nullptr
     */
    FiberAndThread(Fiber::ptr* f, int thr)
        :thread(thr) {
        fiber.swap(*f);
    }

    /**
     * @brief 构造函数
     * @param[in] f 协程执行函数
     * @param[in] thr 线程id
     */
    FiberAndThread(std::function<void()> f, int thr)
        :cb(f), thread(thr) {
    }

    /**
     * @brief 构造函数
     * @param[in] f 协程执行函数指针
     * @param[in] thr 线程id
     * @post *f = nullptr
     */
    FiberAndThread(std::function<void()>* f, int thr)
        :thread(thr) {
        cb.swap(*f);
    }

    /**
     * @brief 无参构造函数
     */
    FiberAndThread()
        :thread(-1) {
    }

    /**
     * @brief 重置数据
     */
    void reset() {
        fiber = nullptr;
        cb = nullptr;
        thread = -1;
    }
};

class Scheduler{
public:
    typedef std::shared_ptr<Scheduler> ptr;
    typedef Mutex MutexType;

    /**
     * @description: 
     * @param {size_t} threads 线程数量
     * @param {bool} use_caller 是否使用当前调用线程
     * @param {string&} name 协程调度器名称
     * 
     * @return {*}
     */
    Scheduler(size_t threads = 1, bool use_caller = true, const std::string& name = "");
    
    /**
     * @description: 析构函数
     * @return {*}
     */
    virtual ~Scheduler();

    /**
     * @description: 返回协程调度器名称
     * @return {*}
     */
    const std::string& getName() const { return m_name;}

    /**
     * @description: 返回当前协程调度器
     * @return {*}
     */
    static Scheduler* GetThis();

    /**
     * @description: 返回当前协程调度器的调度协程
     * @return {*}
     */
    static Fiber* GetMainFiber();

    /**
     * @description: 启动协程调度器
     * @return {*}
     */
    void start();

    /**
     * @description: 停止协程调度器
     * @return {*}
     */
    void stop();

    /**
     * @brief 调度协程
     * @param[in] fc 协程或函数
     * @param[in] thread 协程执行的线程id,-1标识任意线程
     */
    template<class FiberOrCb>
    void schedule(FiberOrCb fc, int thread = -1){
        bool need_tickle = false;
        {
            MutexType::Lock lock(m_mutex);
            need_tickle = scheduleNoLock(fc, thread);
        }

        if(need_tickle){
            tickle();
        }
    }

    template<class InputIterator>
    void schedule(InputIterator begin, InputIterator end){
        bool need_tickle = false;
        {
            MutexType::Lock lock(m_mutex);
            while(begin != end) {
                need_tickle = scheduleNoLock(&*begin, -1) || need_tickle;
                ++begin;
            }
        }
        if(need_tickle) {
            tickle();
        }
    }

    void switchTo(int thread = -1);

    std::ostream& dump(std::ostream& os);

protected:

    /**
     * @description: 通知协程调度器有任务了
     * @return {*}
     */
    virtual void tickle();

    /**
     * @description: 协程调度函数
     * @return {*}
     */
    void run();

    /**
     * @description:  返回是否可以停止
     * @return {*}
     */
    virtual bool stopping();

    /**
     * @description: 协程无任务时可调度执行idle协程 
     * @return {*}
     */
    virtual void idle();

    /**
     * @description: 设置当前的协程调度器 
     * @return {*}
     */
    void setThis();

    /**
     * @description: 是否有空闲线程
     * @return {*}
     */    
    bool hasIdleThreads() {return m_idleThreadCount > 0;}

private:
    /**
     * @description: 将任务插入任务队列（无锁）
     * @return {bool} 如果任务队列为空，返回True（通知协程从idle返回）
     */
    template<class FiberOrCb>
    bool scheduleNoLock(FiberOrCb fc, int thread){
        bool need_tickle = m_fibers.empty();
        FiberAndThread ft(fc, thread);
        if(ft.fiber || ft.cb){
            m_fibers.push_back(ft);
        }
        return need_tickle;
    }

private:
    // Mutex
    MutexType m_mutex;
    // 线程池
    std::vector<Thread::ptr> m_threads;
    // 待执行的协程队列
    std::list<FiberAndThread> m_fibers;
    // user_caller为true时有效，调度协程
    Fiber::ptr m_rootFiber;
    // 协程调度器名称
    std::string m_name;
    
protected:
    // 协程下的线程ID数组
    std::vector<int> m_threadIds;
    // 线程数量
    size_t m_threadCount = 0;
    // 工作线程数量
    std::atomic<size_t> m_activeThreadCount = {0};
    // 空闲线程数量
    std::atomic<size_t> m_idleThreadCount = {0};
    /// 是否正在停止
    bool m_stopping = true;
    /// 是否自动停止
    bool m_autoStop = false;
    /// 主线程id(use_caller)
    int m_rootThread = 0;
};

}


#endif