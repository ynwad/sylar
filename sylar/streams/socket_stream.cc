/*
 * @Author: Ynwad_
 * @Date: 2022-12-08 21:54:01
 * @LastEditors: Ynwad_ qingchenchn@gmail.com
 * @LastEditTime: 2022-12-08 22:49:48
 * @FilePath: /sylar/sylar/streams/socket_stream.cc
 * @Description: 
 * 
 * Copyright (c) 2022 by Ynwad_ qingchenchn@gmail.com, All Rights Reserved. 
 */
#include "socket_stream.h"
#include "sylar/utils.h"

namespace sylar {

SocketStream::SocketStream(Socket::ptr sock, bool owner)
    :m_socket(sock)
    ,m_owner(owner) {
}

SocketStream::~SocketStream() {
    if(m_owner && m_socket) {
        m_socket->close();
    }
}

bool SocketStream::isConnected() const {
    return m_socket && m_socket->isConnected();
}

int SocketStream::read(void* buffer, size_t length) {
    if(!isConnected()) {
        return -1;
    }
    return m_socket->recv(buffer, length);
}

int SocketStream::read(ByteArray::ptr ba, size_t length) {
    if(!isConnected()) {
        return -1;
    }
    std::vector<iovec> iovs;
    ba->getWriteBuffers(iovs, length);
    int rt = m_socket->recv(&iovs[0], iovs.size());
    if(rt > 0) {
        ba->setPosition(ba->getPosition() + rt);
    }
    return rt;
}

int SocketStream::write(const void* buffer, size_t length) {
    if(!isConnected()) {
        return -1;
    }
    return m_socket->send(buffer, length);
}

int SocketStream::write(ByteArray::ptr ba, size_t length) {
    if(!isConnected()) {
        return -1;
    }
    std::vector<iovec> iovs;
    ba->getReadBuffers(iovs, length);
    int rt = m_socket->send(&iovs[0], iovs.size());
    if(rt > 0) {
        ba->setPosition(ba->getPosition() + rt);
    }
    return rt;
}

void SocketStream::close() {
    if(m_socket) {
        m_socket->close();
    }
}

Address::ptr SocketStream::getRemoteAddress() {
    if(m_socket) {
        return m_socket->getRemoteAddress();
    }
    return nullptr;
}

Address::ptr SocketStream::getLocalAddress() {
    if(m_socket) {
        return m_socket->getLocalAddress();
    }
    return nullptr;
}

std::string SocketStream::getRemoteAddressString() {
    auto addr = getRemoteAddress();
    if(addr) {
        return addr->toString();
    }
    return "";
}

std::string SocketStream::getLocalAddressString() {
    auto addr = getLocalAddress();
    if(addr) {
        return addr->toString();
    }
    return "";
}

}
