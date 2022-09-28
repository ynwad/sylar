#include "log.h"
#include <map>
#include <functional>
#include <memory>
#include "utils.h"
#include <execinfo.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "config.h"

namespace sylar{

std::string LogLevel::ToString(Level level){
    switch(level){
#define XX(name) \
    case LogLevel::name: \
        return #name; \
        break;

    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX
    default:
        return "UNKNOW";
    }
    return "UNKNOW";
}

LogLevel::Level LogLevel::FromString(const std::string& str){
#define XX(level, v) \
    if(str == #v){ \
        return LogLevel::level; \
    }

    XX(DEBUG, debug);
    XX(INFO, info);
    XX(WARN, warn);
    XX(ERROR, error);
    XX(FATAL, fatal);

    XX(DEBUG, DEBUG);
    XX(INFO, INFO);
    XX(WARN, WARN);
    XX(ERROR, ERROR);
    XX(FATAL, FATAL);
    return LogLevel::UNKNOW;
#undef XX
}


LogEventWrap::LogEventWrap(LogEvent::ptr e)
    :m_event(e) {
}

LogEventWrap::~LogEventWrap() {
    m_event->getLogger()->log(m_event->getLevel(), m_event);
}

LogEvent::LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level
            ,const char* file, int32_t line, uint32_t elapse
            ,uint32_t thread_id, uint32_t fiber_id, uint64_t time
            ,const std::string& thread_name)
    :m_file(file)
    ,m_line(line)
    ,m_elapse(elapse)
    ,m_threadId(thread_id)
    ,m_fiberId(fiber_id)
    ,m_time(time)
    ,m_threadName(thread_name)
    ,m_logger(logger)
    ,m_level(level) {
}

Logger::Logger(const std::string& name)
    :m_level(LogLevel::DEBUG)
    ,m_name(name){
    m_formatter.reset(new LogFormatter("%d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n"));
}

void Logger::addAppender(LogAppender::ptr appender){
    MutexType::Lock lock(m_mutex);
    if(!appender->getFormatter()){
        MutexType::Lock ll(appender->m_mutex);
        appender->m_formatter = m_formatter;
    }
    m_lstAppenders.emplace_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender){
    MutexType::Lock lock(m_mutex);
    for(auto it = m_lstAppenders.begin(); it != m_lstAppenders.end(); ++it){
        if(*it == appender){
            m_lstAppenders.erase(it);
            break;
        }
    }
}

void Logger::clearAppender(){
    MutexType::Lock lock(m_mutex);
    m_lstAppenders.clear();
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event){
    if(level >= m_level){
        auto self = shared_from_this();
        MutexType::Lock lock(m_mutex); //局部锁，栈退出后，析构函数会将其释放
        if(!m_lstAppenders.empty()){
            for(auto& i : m_lstAppenders){
                i->log(self, level, event);
            }
        }
        else if(m_root) {
            m_root->log(level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event){
    log(LogLevel::DEBUG, event);
}

void Logger::info(LogEvent::ptr event){
    log(LogLevel::INFO, event);
}

void Logger::warn(LogEvent::ptr event){
    log(LogLevel::WARN, event);
}

void Logger::error(LogEvent::ptr event){
    log(LogLevel::ERROR, event);
}

void Logger::fatal(LogEvent::ptr event){
    log(LogLevel::FATAL, event);
}

void Logger::setFormatter(LogFormatter::ptr val){
    MutexType::Lock lock(m_mutex);
    m_formatter = val;

    for(auto& i : m_lstAppenders) {
        MutexType::Lock ll(i->m_mutex);
        if(!i->m_hasFormatter){
            i->m_formatter = m_formatter;
        }
    }
}

void Logger::setFormatter(const std::string& val){
    sylar::LogFormatter::ptr new_val(new sylar::LogFormatter(val));
    if(new_val->isError()){
        std::cout << "Logger setFormatter name=" << m_name
                  << " value=" << val << " invalid formattern"
                  << std::endl;
        return;
    }

    setFormatter(new_val);
}

std::string Logger::toYamlString() {
    // MutexType::Lock lock(m_mutex);
    YAML::Node node;
    node["name"] = m_name;
    if(m_level != LogLevel::UNKNOW) {
        node["level"] = LogLevel::ToString(m_level);
    }
    if(m_formatter) {
        node["formatter"] = m_formatter->getPattern();
    }

    for(auto& i : m_lstAppenders) {
        node["appenders"].push_back(YAML::Load(i->toYamlString()));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}


void LogAppender::setFormatter(LogFormatter::ptr val){
    m_formatter = val;

    if(m_formatter){
        m_hasFormatter = true;
    }
    else{
        m_hasFormatter = false;
    }
}

void StdOutLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event){
    if(level >= m_level){
        MutexType::Lock lock(m_mutex);
        m_formatter->format(std::cout, logger, level, event);
    }
}

std::string StdOutLogAppender::toYamlString(){
    YAML::Node node;
    node["type"] = "StdoutLogAppender";
    if(m_level != LogLevel::UNKNOW) {
        node["level"] = LogLevel::ToString(m_level);
    }
    if(m_hasFormatter && m_formatter) {
        node["formatter"] = m_formatter->getPattern();
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

FileLogAppender::FileLogAppender(const std::string filename)
    :m_filename(filename){
    reopen();
}

void FileLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event){
    if(level >= m_level){
        uint64_t now = event->getTime();
        if(now >= (m_lastTime + 3)){
            reopen();
            m_lastTime = now;
        }
        MutexType::Lock lock(m_mutex);
        if(!m_formatter->format(m_filestream, logger, level, event)){
            std::cout << "error" <<std::endl;
        }
    }
}

std::string FileLogAppender::toYamlString(){
    YAML::Node node;
    node["type"] = "FileLogAppender";
    node["file"] = m_filename;
    if(m_level != LogLevel::UNKNOW) {
        node["level"] = LogLevel::ToString(m_level);
    }
    if(m_hasFormatter && m_formatter) {
        node["formatter"] = m_formatter->getPattern();
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

bool FileLogAppender::reopen(){
    MutexType::Lock lock(m_mutex);
    if(m_filestream) {
        m_filestream.close();
    }
    return FSUtil::OpenForWrite(m_filestream, m_filename, std::ios::app);
}

class MessageFormatItem : public LogFormatter::FormatItem {
public:
    MessageFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getContent();
    }
};

class LevelFormatItem : public LogFormatter::FormatItem {
public:
    LevelFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << LogLevel::ToString(level);
    }
};

class ElapseFormatItem : public LogFormatter::FormatItem {
public:
    ElapseFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getElapse();
    }
};

class NameFormatItem : public LogFormatter::FormatItem {
public:
    NameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getLogger()->getName();
    }
};

class ThreadIdFormatItem : public LogFormatter::FormatItem {
public:
    ThreadIdFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getThreadId();
    }
};

class FiberIdFormatItem : public LogFormatter::FormatItem {
public:
    FiberIdFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getFiberId();
    }
};

class ThreadNameFormatItem : public LogFormatter::FormatItem {
public:
    ThreadNameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getThreadName();
    }
};

class DateTimeFormatItem : public LogFormatter::FormatItem {
public:
    DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%S")
        :m_format(format) {
        if(m_format.empty()) {
            m_format = "%Y-%m-%d %H:%M:%S";
        }
    }

    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        struct tm tm;
        time_t time = event->getTime();
        localtime_r(&time, &tm);
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &tm);
        os << buf;
    }
private:
    std::string m_format;
};

class FilenameFormatItem : public LogFormatter::FormatItem {
public:
    FilenameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getFile();
    }
};

class LineFormatItem : public LogFormatter::FormatItem {
public:
    LineFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getLine();
    }
};

class NewLineFormatItem : public LogFormatter::FormatItem {
public:
    NewLineFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << std::endl;
    }
};


class StringFormatItem : public LogFormatter::FormatItem {
public:
    StringFormatItem(const std::string& str)
        :m_string(str) {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << m_string;
    }
private:
    std::string m_string;
};

class TabFormatItem : public LogFormatter::FormatItem {
public:
    TabFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override {
        os << "\t";
    }
private:
    std::string m_string;
};

LogFormatter::LogFormatter(const std::string pattern)
    :m_pattern(pattern){
        init();
}

std::string LogFormatter::format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event){
    std::stringstream ss;
    for(auto ite : m_vecItems){
        ite->format(ss, logger, level, event);
    }
    return ss.str();
}

std::ostream& LogFormatter::format(std::ostream& ofs, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event){
    for(auto ite : m_vecItems){
        ite->format(ofs, logger, level, event);
    }
    return ofs;
}

void LogFormatter::init() {
    //str, format, type
    std::vector<std::tuple<std::string, std::string, int> > vec;
    std::string nstr;
    // %d{%Y-%m-%d %H:%M:%S}%T%t%T%N%T%F%T[%p]%T[%c]%T%f:%l%T%m%n
    for(size_t i = 0; i < m_pattern.size(); ++i) {
        if(m_pattern[i] != '%') {
            nstr.append(1, m_pattern[i]);
            continue;
        }

        if((i + 1) < m_pattern.size()) {
            if(m_pattern[i + 1] == '%') {
                nstr.append(1, '%');
                continue;
            }
        }

        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;
        std::string fmt;
        while(n < m_pattern.size()) {
            if(!fmt_status && (!isalpha(m_pattern[n]) && m_pattern[n] != '{'
                    && m_pattern[n] != '}')) {
                str = m_pattern.substr(i + 1, n - i - 1);
                break;
            }
            if(fmt_status == 0) {
                if(m_pattern[n] == '{') {
                    str = m_pattern.substr(i + 1, n - i - 1);
                    //std::cout << "*" << str << std::endl;
                    fmt_status = 1; //解析格式
                    fmt_begin = n;
                    ++n;
                    continue;
                }
            } else if(fmt_status == 1) {
                if(m_pattern[n] == '}') {
                    fmt = m_pattern.substr(fmt_begin + 1, n - fmt_begin - 1);
                    //std::cout << "#" << fmt << std::endl;
                    fmt_status = 0;
                    ++n;
                    break;
                }
            }
            ++n;
            if(n == m_pattern.size()) {
                if(str.empty()) {
                    str = m_pattern.substr(i + 1);
                }
            }
        }

        if(fmt_status == 0) {
            if(!nstr.empty()) {
                vec.push_back(std::make_tuple(nstr, std::string(), 0));
                nstr.clear();
            }
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n - 1;
        } else if(fmt_status == 1) {
            std::cout << "pattern parse error: " << m_pattern << " - " << m_pattern.substr(i) << std::endl;
            m_error = true;
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 0));
        }
    }

    if(!nstr.empty()) {
        vec.push_back(std::make_tuple(nstr, "", 0));
    }
    static std::map<std::string, std::function<FormatItem::ptr(const std::string& str)> >  s_format_items = {
#define XX(str, C) \
        {#str, [](const std::string& fmt) { return FormatItem::ptr(new C(fmt));}}

        XX(m, MessageFormatItem),           //m:消息
        XX(p, LevelFormatItem),             //p:日志级别
        XX(r, ElapseFormatItem),            //r:累计毫秒数
        XX(c, NameFormatItem),              //c:日志名称
        XX(t, ThreadIdFormatItem),          //t:线程id
        XX(n, NewLineFormatItem),           //n:换行
        XX(d, DateTimeFormatItem),          //d:时间
        XX(f, FilenameFormatItem),          //f:文件名
        XX(l, LineFormatItem),              //l:行号
        XX(T, TabFormatItem),               //T:Tab
        XX(F, FiberIdFormatItem),           //F:协程id
        XX(N, ThreadNameFormatItem),        //N:线程名称
#undef XX
    };

    for(auto& i : vec) {
        if(std::get<2>(i) == 0) {
            m_vecItems.push_back(FormatItem::ptr(new StringFormatItem(std::get<0>(i))));
        } else {
            auto it = s_format_items.find(std::get<0>(i));
            if(it == s_format_items.end()) {
                m_vecItems.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
                m_error = true;
            } else {
                m_vecItems.push_back(it->second(std::get<1>(i)));
            }
        }

        // std::cout << "(" << std::get<0>(i) << ") - (" << std::get<1>(i) << ") - (" << std::get<2>(i) << ")" << std::endl;
    }
    // std::cout << m_vecItems.size() << std::endl;
    // std::cout << m_vecItems.size() << std::endl;
}

LoggerManager::LoggerManager() {
    m_root.reset(new Logger);
    m_root->addAppender(LogAppender::ptr(new StdOutLogAppender));

    m_loggers[m_root->m_name] = m_root;

    init();
}

Logger::ptr LoggerManager::getLogger(const std::string& name) {
    MutexType::Lock lock(m_mutex);
    auto it = m_loggers.find(name);
    if(it != m_loggers.end()) {
        return it->second;
    }

    Logger::ptr logger(new Logger(name));
    logger->m_root = m_root;
    m_loggers[name] = logger;
    return logger;
}

std::string LoggerManager::toYamlString() {
    // MutexType::Lock lock(m_mutex);
    YAML::Node node;
    for(auto& i : m_loggers) {
        node.push_back(YAML::Load(i.second->toYamlString()));
    }
    std::stringstream ss;
    ss << node;
    return ss.str();
}

void LoggerManager::init() {

}

struct LogAppenderDefine{
    int nType = 0; //1 File, 2 stdout
    LogLevel::Level level = LogLevel::UNKNOW;
    std::string formatter;
    std::string file;

    bool operator==(const LogAppenderDefine& oth) const{
        return nType == oth.nType
                && level == oth.level
                && formatter == oth.formatter
                && file == oth.file;
    }
};

struct LogDefine{
    std::string name;
    LogLevel::Level level = LogLevel::UNKNOW;
    std::string formatter;
    std::vector<LogAppenderDefine> vecAppender;

    bool operator==(const LogDefine& oth) const{
        return name == oth.name
                && level == oth.level
                && formatter == oth.formatter
                && vecAppender == oth.vecAppender;
    }

    bool operator<(const LogDefine& oth) const {
        return name < oth.name;
    }
};

template<>
class LexicalCast<LogDefine, std::string> {
public:
    std::string operator()(const LogDefine& i){
        YAML::Node node;
        node["name"] = i.name;
        if(i.level != LogLevel::UNKNOW){
            node["level"] = sylar::LogLevel::ToString(i.level);
        }
        if(!i.formatter.empty()) {
            node["formatter"] = i.formatter;
        }

        for(auto& a : i.vecAppender){
            YAML::Node  subNode;
            if(a.nType == 1) {
                subNode["type"] = "FileLogAppender";
                subNode["file"] = a.file;
            } else if(a.nType == 2) {
                subNode["type"] = "StdoutLogAppender";
            }

            if(a.level != LogLevel::UNKNOW) {
                subNode["level"] = LogLevel::ToString(a.level);
            }

            if(!a.formatter.empty()) {
                subNode["formatter"] = a.formatter;
            }

            node["appenders"].push_back(subNode);
        }

        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

template<>
class LexicalCast<std::string, LogDefine> {
public:
    LogDefine operator()(const std::string& str){
        YAML::Node node = YAML::Load(str);
        LogDefine ld;
        if(!node["name"].IsDefined()){
            std::cout << "log config error: name is null, " << node
                      << std::endl;
            throw std::logic_error("log config name is null");
        }
        ld.name = node["name"].as<std::string>();
        ld.level = LogLevel::FromString(node["level"].IsDefined() ? node["level"].as<std::string>() : "");
        if(node["formatter"].IsDefined()){
            ld.formatter = node["formatter"].as<std::string>();
        }

        if(node["appenders"].IsDefined() && node["appenders"].IsSequence()){
            for(size_t i = 0; i < node["appenders"].size(); ++i){
                auto a = node["appenders"][i];
                if(!a["type"].IsDefined()){
                    std::cout << "log config error: appender type is null, " << a
                              << std::endl;
                    continue;
                }
                std::string type = a["type"].as<std::string>();
                LogAppenderDefine lad;
                if(type == "FileLogAppender"){
                    lad.nType = 1;
                    if(!a["file"].IsDefined()){
                        std::cout << "log config error: fileappender file is null, " << a
                              << std::endl;
                        continue;
                    }
                    lad.file = a["file"].as<std::string>();
                    if(a["formatter"].IsDefined()){
                        lad.formatter = a["formatter"].as<std::string>();
                    }
                }else if(type == "StdOutAppender"){
                    lad.nType = 2;
                    if(a["formatter"].IsDefined()){
                        lad.formatter = a["formatter"].as<std::string>();
                    }
                }else{
                    std::cout << "log config error: appender type is invalid, " << a
                              << std::endl;
                    continue;
                }
                if(a["level"].IsDefined()){
                    lad.level = sylar::LogLevel::FromString(a["level"].as<std::string>());
                }

                ld.vecAppender.push_back(lad);
            }
        }
        return ld;
    }
};


sylar::ConfigVar<std::set<LogDefine>>::ptr g_log_defines = 
    sylar::Config::Lookup("logs", std::set<LogDefine>(), "logs config");

struct LogIniter {
    LogIniter() {
        g_log_defines->addListener([](const std::set<LogDefine> old_value, 
                    const std::set<LogDefine> new_value){
            SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "on_logger_conf_changed";
            for(auto &i : new_value){
                auto ite = old_value.find(i);
                sylar::Logger::ptr logger;
                if(ite == old_value.end()){
                    //新增logger
                    logger = SYLAR_LOG_NAME(i.name);
                }
                logger->setLevel(i.level);
                if(!i.formatter.empty())
                {
                    logger->setFormatter(i.formatter);
                }
                logger->clearAppender();
                for(auto &appender : i.vecAppender){
                    sylar::LogAppender::ptr ap;
                    if(appender.nType == 1){
                        ap.reset(new sylar::FileLogAppender(appender.file));
                    }else if(appender.nType == 2){
                        ap.reset(new sylar::StdOutLogAppender());
                    }
                    
                    ap->setLevel(appender.level);
                    
                    if(!appender.formatter.empty()){
                        LogFormatter::ptr fmt(new LogFormatter(appender.formatter));
                        ap->setFormatter(fmt);
                        if(!fmt->isError()) {
                            ap->setFormatter(fmt);
                        } else {
                            std::cout << "log.name=" << i.name << " appender type=" << appender.nType
                                    << " formatter=" << appender.formatter << " is invalid" << std::endl;
                        }
                    }

                    logger->addAppender(ap);
                }
            }

            for(auto &i : old_value){
                auto ite = new_value.find(i);
                if(ite == new_value.end()){
                    //删除Logger
                    auto logger = SYLAR_LOG_NAME(i.name);
                    logger->setLevel((LogLevel::Level)100);
                    logger->clearAppender();
                }
            }
        });
    }
};

static LogIniter __log_init;

}
