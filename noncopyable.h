<<<<<<< HEAD
#ifndef __SYLAR_NONCOPYABLE_H__
#define __SYLAR_NONCOPYABLE_H__

namespace sylar{
=======
#ifndef __YNWAD_NONCOPYABLE_H__
#define __YNWAD_NONCOPYABLE_H__

namespace ynwad{
>>>>>>> b996627ff76fe6b1dcb3115480d7245e7a1d779c
class Noncopyable {
public:
    /**
     * @brief 默认构造函数
     */ 
    Noncopyable() = default;

    /**
     * @brief 默认析构函数
     */
    ~Noncopyable() = default;

    /**
     * @brief 拷贝构造函数(禁用)
     */
    Noncopyable(const Noncopyable&) = delete;

    /**
     * @brief 赋值函数(禁用)
     */
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}



#endif