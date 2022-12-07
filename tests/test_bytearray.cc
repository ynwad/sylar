/*
 * @Author: Ynwad_
 * @Date: 2022-12-06 23:44:30
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-12-07 01:18:05
 * @FilePath: /sylar/tests/test_bytearray.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#ifndef __Test__
#define __Test__
#include "sylar/bytearray.h"
#include "sylar/sylar.h"
#include <string>

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

class  person2{
public:
    person2(){}
    person2(const std::string &s, const int32_t a)
        :name(s), age(a){
    }
    void bytearray(const std::string &path){
        sylar::ByteArray::ptr ba(new sylar::ByteArray());
        ba->writeStringVint(name);
        ba->writeFint32(age);
        ba->setPosition(0);
        ba->writeToFile(path);
    }
    
    void frombytearray(const std::string &path){
        sylar::ByteArray::ptr ba2(new sylar::ByteArray());
        SYLAR_ASSERT(ba2->readFromFile(path));
        ba2->setPosition(0);
        name = ba2->readStringVint();
        age = ba2->readFint32();
    }

    std::string name = "name";
    int32_t age = 100;
};

void test() {
#define XX(type, len, write_fun, read_fun, base_len) {\
    std::vector<type> vec; \
    for(int i = 0; i < len; ++i) { \
        vec.push_back(std::rand()); \
    } \
    sylar::ByteArray::ptr ba(new sylar::ByteArray(base_len)); \
    for(auto& i : vec) { \
        ba->write_fun(i); \
    } \
    ba->setPosition(0); \
    for(size_t i = 0; i < vec.size(); ++i) { \
        type v = ba->read_fun(); \
        SYLAR_ASSERT(v == vec[i]); \
    } \
    SYLAR_ASSERT(ba->getReadSize() == 0); \
    SYLAR_LOG_INFO(g_logger) << #write_fun "/" #read_fun \
                    " (" #type " ) len=" << len \
                    << " base_len=" << base_len \
                    << " size=" << ba->getSize(); \
}

    XX(int8_t,  100, writeFint8, readFint8, 1);
    XX(uint8_t, 100, writeFuint8, readFuint8, 1);
    XX(int16_t,  100, writeFint16,  readFint16, 1);
    XX(uint16_t, 100, writeFuint16, readFuint16, 1);
    XX(int32_t,  100, writeFint32,  readFint32, 1);
    XX(uint32_t, 100, writeFuint32, readFuint32, 1);
    XX(int64_t,  100, writeFint64,  readFint64, 1);
    XX(uint64_t, 100, writeFuint64, readFuint64, 1);

    XX(int32_t,  100, writeInt32,  readInt32, 1);
    XX(uint32_t, 100, writeUint32, readUint32, 1);
    XX(int64_t,  100, writeInt64,  readInt64, 1);
    XX(uint64_t, 100, writeUint64, readUint64, 1);
#undef XX

#define XX(type, len, write_fun, read_fun, base_len) {\
    std::vector<type> vec; \
    for(int i = 0; i < len; ++i) { \
        vec.push_back(rand()); \
    } \
    sylar::ByteArray::ptr ba(new sylar::ByteArray(base_len)); \
    for(auto& i : vec) { \
        ba->write_fun(i); \
    } \
    ba->setPosition(0); \
    for(size_t i = 0; i < vec.size(); ++i) { \
        type v = ba->read_fun(); \
        SYLAR_ASSERT(v == vec[i]); \
    } \
    SYLAR_ASSERT(ba->getReadSize() == 0); \
    SYLAR_LOG_INFO(g_logger) << #write_fun "/" #read_fun \
                    " (" #type " ) len=" << len \
                    << " base_len=" << base_len \
                    << " size=" << ba->getSize(); \
    ba->setPosition(0); \
    SYLAR_ASSERT(ba->writeToFile("/tmp/" #type "_" #len "-" #read_fun ".dat")); \
    sylar::ByteArray::ptr ba2(new sylar::ByteArray(base_len * 2)); \
    SYLAR_ASSERT(ba2->readFromFile("/tmp/" #type "_" #len "-" #read_fun ".dat")); \
    ba2->setPosition(0); \
    SYLAR_LOG_INFO(g_logger) << ba2->toString(); \
    SYLAR_ASSERT(ba->toString() == ba2->toString()); \
    SYLAR_ASSERT(ba->getPosition() == 0); \
    SYLAR_ASSERT(ba2->getPosition() == 0); \
}
    XX(int8_t,  100, writeFint8, readFint8, 1);
    XX(uint8_t, 100, writeFuint8, readFuint8, 1);
    XX(int16_t,  100, writeFint16,  readFint16, 1);
    XX(uint16_t, 100, writeFuint16, readFuint16, 1);
    XX(int32_t,  100, writeFint32,  readFint32, 1);
    XX(uint32_t, 100, writeFuint32, readFuint32, 1);
    XX(int64_t,  100, writeFint64,  readFint64, 1);
    XX(uint64_t, 100, writeFuint64, readFuint64, 1);

    XX(int32_t,  100, writeInt32,  readInt32, 1);
    XX(uint32_t, 100, writeUint32, readUint32, 1);
    XX(int64_t,  100, writeInt64,  readInt64, 1);
    XX(uint64_t, 100, writeUint64, readUint64, 1);

#undef XX
}

void test2(){
    sylar::ByteArray::ptr ba(new sylar::ByteArray());
    // ba->writeInt32(111);
    std::string s = "188888ssxxxxxxxxxxxxx23";
    ba->writeStringVint(s);
    ba->writeFint32(789654);
    ba->setPosition(0);

    // SYLAR_LOG_INFO(g_logger) << ba->toString();

    ba->writeToFile("./bbbyte.dat");
    sylar::ByteArray::ptr ba2(new sylar::ByteArray());
    SYLAR_ASSERT(ba2->readFromFile("./bbbyte.dat"));
    ba2->setPosition(0);
    SYLAR_LOG_INFO(g_logger) << ba2->readStringVint() << " ::: " << ba2->readFint32();
}

void test3(){
    person2 p1("test1111111", 19999);
    p1.bytearray("./bbbyte2.dat");
    person2 p2;
    SYLAR_LOG_INFO(g_logger) << p2.name << " ::: " << p2.age;
    p2.frombytearray("./bbbyte2.dat");
    SYLAR_LOG_INFO(g_logger) << p2.name << " ::: " << p2.age;
}

int main(int argc, char** argv) {
    test3();
    return 0;
}


#endif