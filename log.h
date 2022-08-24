<<<<<<< HEAD
#ifndef __SYLAR_LOG_H__
#define __SYLAR_LOG_H__
=======
#ifndef __YNWAD_LOG_H__
#define __YNWAD_LOG_H__
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c

#include <string>
#include <stdint.h>
#include <memory>
#include <list>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "macro.h"
#include "mutex.h"
<<<<<<< HEAD
#include "sigleton.h"
#include "thread.h"

/**
 * @brief 使用流式方式将日志级别level的日志写入到logger
 */
#define SYLAR_LOG_LEVEL(logger, level) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
                __FILE__, __LINE__, 0, sylar::GetThreadId(), \
            sylar::GetFiberId(), time(0), sylar::Thread::GetName()))).getSS()

/**
 * @brief 使用流式方式将日志级别debug的日志写入到logger
 */
#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::DEBUG)

/**
 * @brief 使用流式方式将日志级别info的日志写入到logger
 */
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::INFO)

/**
 * @brief 使用流式方式将日志级别warn的日志写入到logger
 */
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::WARN)

/**
 * @brief 使用流式方式将日志级别error的日志写入到logger
 */
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::ERROR)

/**
 * @brief 使用流式方式将日志级别fatal的日志写入到logger
 */
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger, sylar::LogLevel::FATAL)


#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()
/**
 * @brief 使用格式化方式将日志级别level的日志写入到logger
 */
#define SYLAR_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if(logger->getLevel() <= level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger, level, \
            __FILE__, __LINE__, 0, sylar::GetThreadId(), \
            sylar::GetFiberId(), time(0), sylar::Thread::GetName()))).getEvent->format(fmt, __VA_ARGS__)
=======

>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c

/**
 * @brief 获取name的日志器
 */
<<<<<<< HEAD
#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::GetInstance()->getLogger(name)

namespace sylar {
=======
#define SYLAR_LOG_NAME(name) ynwad::LoggerMgr::GetInstance()->getLogger(name)

namespace ynwad {
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c


class Logger;

//日志级别
class LogLevel {
public:
    enum Level {
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    static std::string ToString(Level level);
};

//日志事件
class LogEvent {
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
            ,const char* file, int32_t line, uint32_t elapse
            ,uint32_t thread_id, uint32_t fiber_id, uint64_t time
            ,const std::string& thread_name);

    const char* getFile() const {return m_file;}
        /**
     * @brief 返回行号
     */
    int32_t getLine() const { return m_line;}

    /**
     * @brief 返回耗时
     */
    uint32_t getElapse() const { return m_elapse;}

    /**
     * @brief 返回线程ID
     */
    uint32_t getThreadId() const { return m_threadId;}

    /**
     * @brief 返回协程ID
     */
    uint32_t getFiberId() const { return m_fiberId;}

    /**
     * @brief 返回时间
     */
    uint64_t getTime() const { return m_time;}

    /**
     * @brief 返回线程名称
     */
    const std::string& getThreadName() const { return m_threadName;}
    /**
     * @brief 返回日志内容
     */
    std::string getContent() const { return m_ss.str();}

    /**
     * @brief 返回日志内容字符串流
     */
    std::stringstream& getSS() { return m_ss;}

    LogLevel::Level getLevel() const {return m_level;}

    /**
     * @brief 返回日志器
     */
    std::shared_ptr<Logger> getLogger() const {return m_logger;}
private:
    const char* m_file = nullptr;   //文件名
    uint32_t m_line = 0;    //行号
    uint32_t m_elapse = 0;  //程序启动开始到现在的毫秒数
    uint32_t m_threadId = 0;    //线程Id
    uint32_t m_fiberId = 0;     //协程id
    uint64_t m_time = 0;        //时间戳
    std::string m_content;      //日志内容
    /// 线程名称
    std::string m_threadName;
    /// 日志内容流
    std::stringstream m_ss;
    /// 日志器
    std::shared_ptr<Logger> m_logger;
    /// 日志等级
    LogLevel::Level m_level;
};

//事件
class LogEventWrap{
public:
    LogEventWrap(LogEvent::ptr event);

    ~LogEventWrap();

    LogEvent::ptr getEvent() const{return m_event;}

    std::stringstream& getSS() {return m_event->getSS();};
private:
    LogEvent::ptr m_event;

};

//日志格式器
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string pattern);
    //%t %thread_id %m%n
    std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);
public:
    class FormatItem{
    public:
        typedef std::shared_ptr<FormatItem> ptr;
        virtual ~FormatItem(){}
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
    };
    
    void init();

    bool isError() const {return m_error;}

    const std::string getPattern() const {return m_pattern;}
private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_vecItems;
    bool    m_error = false;
};

//日志输出地
class LogAppender {
friend class Logger;
public:
    typedef std::shared_ptr<LogAppender> ptr;
    typedef Spinlock MutexType;

    virtual ~LogAppender() {}

    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
<<<<<<< HEAD
    void setFormatter(LogFormatter::ptr val);
=======
    void setFormatter(LogFormatter::ptr val) {m_formatter = val;}
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c
    LogFormatter::ptr getFormatter() {return m_formatter;}
    LogLevel::Level getLevel() {return m_level;}
    void setLevel(LogLevel::Level level){m_level = level;}
protected:
    // 日志级别
    LogLevel::Level m_level = LogLevel::DEBUG;
    // 是否有自己的日志格式器
    bool m_hasFormatter = false;
    // 日志格式器
    LogFormatter::ptr m_formatter;
    // mutex
    MutexType m_mutex;
};

//日志器
class Logger : public std::enable_shared_from_this<Logger> {
    friend class LoggerManager;
public:
    typedef std::shared_ptr<Logger> ptr;
    typedef Spinlock MutexType;
    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, LogEvent::ptr event);
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);
    
    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppender();
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level level) {m_level = level;}
    const std::string& getName() const {return m_name;}

    /**
     * @brief 设置日志格式器
     */
    void setFormatter(LogFormatter::ptr val);

    /**
     * @brief 设置日志格式模板
     */
    void setFormatter(const std::string& val);

    /**
     * @brief 获取日志格式器
     */
    LogFormatter::ptr getFormatter(){return m_formatter;}

private:
    LogLevel::Level m_level;       //日志级别
    std::string m_name;     //日志名称
    /// 日志格式器
    LogFormatter::ptr m_formatter;
    std::list<LogAppender::ptr> m_lstAppenders;      //Appender集合
    MutexType m_mutex;
    Logger::ptr m_root;
};


//输出到控制台的Appender
class StdOutLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<StdOutLogAppender> ptr;
    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
};

//输出到文件的Appender
class FileLogAppender : public LogAppender {
public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    FileLogAppender(const std::string filename);
    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;

    bool reopen();
private:
    std::string m_filename;     //文件名
    std::ofstream   m_filestream;
    // 上次重新打开的时间
    uint64_t m_lastTime = 0;
};

/**
 * @brief 日志器管理类
 */

class LoggerManager {
public:
    typedef Spinlock MutexType;

        /**
     * @brief 构造函数
     */
    LoggerManager();

    /**
     * @brief 获取日志器
     * @param[in] name 日志器名称
     */
    Logger::ptr getLogger(const std::string& name);

    /**
     * @brief 初始化
     */
    void init();

    /**
     * @brief 返回主日志器
     */
    Logger::ptr getRoot() const { return m_root;}

    /**
     * @brief 将所有的日志器配置转成YAML String
     */
    std::string toYamlString();
private:
    /// Mutex
    MutexType m_mutex;
    /// 日志器容器
    std::map<std::string, Logger::ptr> m_loggers;
    /// 主日志器
    Logger::ptr m_root;
};

/// 日志器管理类单例模式
<<<<<<< HEAD
typedef sylar::Sigleton<LoggerManager> LoggerMgr;
=======
typedef ynwad::Singleton<LoggerManager> LoggerMgr;
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c

}


#endif


