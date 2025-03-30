#include "SocketHandle.h"

SocketHandle::SocketHandle(int server_fd)
    : server_fd_(server_fd)
{
    if (server_fd < 0)
    {
        throw std::runtime_error("Failed to create socket");
    }
}

SocketHandle::~SocketHandle() {
    if (server_fd_ >= 0) {
        close(server_fd_);
    }
}

int SocketHandle::get() const {
    return server_fd_;
}