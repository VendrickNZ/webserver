#ifndef SOCKETHANDLE_H
#define SOCKETHANDLE_H

#include <stdexcept>
#include <sys/socket.h>
#include <unistd.h>

class SocketHandle
{
public:
    SocketHandle(int server_fd);
    ~SocketHandle();

    SocketHandle(const SocketHandle&) = delete;
    SocketHandle& operator=(const SocketHandle&) = delete;

    int get() const;

private:
    int server_fd_;
};

#endif