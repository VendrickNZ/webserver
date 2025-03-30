#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdexcept>
#include "SocketHandle.h"

#define MAX_BUFFER_SIZE 30000
#define SERVER_PORT 3000

int createSocket()
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to create socket");
    }
    return server_fd;
}

sockaddr_in createAddress()
{
    sockaddr_in address{};

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(SERVER_PORT);

    return address;
}

void bindSocket(SocketHandle& socket, sockaddr_in& address)
{
    int bindStatus = bind(socket.get(), (sockaddr *)&address, sizeof(address));
    if (bindStatus == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to bind socket");
    }
    int listenStatus = listen(socket.get(), 3);
    if (listenStatus == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to listen on socket");
    }
}

int acceptConnection(SocketHandle& socket, sockaddr_in& address)
{
    int addrlen = sizeof(address);
    int new_socket = accept(socket.get(), (sockaddr *)&address, (socklen_t *)&addrlen);
    if (new_socket == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to accept request on socket");
    }
    return new_socket;
}

void response(int new_socket)
{
    char buffer[MAX_BUFFER_SIZE] = {0};
    int readStatus = read(new_socket, buffer, MAX_BUFFER_SIZE);
    if (readStatus == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to read on socket");
    }
    std::cout << "Request received:\r\n"
              << buffer << "\r\n";

    const char *response =
        "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: 48\r\n\r\n"
        "<html><body><h1>Hello World!</h1></body></html>";

    int writeStatus = write(new_socket, response, strlen(response));
    if (writeStatus == -1) {
        throw std::system_error(errno, std::generic_category(), "Failed to write on socket");
    }
    close(new_socket);
}

int main()
{
    try {
        int server_fd = createSocket();
        SocketHandle socket = SocketHandle(server_fd);
        sockaddr_in address = createAddress();
        bindSocket(socket, address);
        std::cout << "Server listening on port 3000\n";

        while (true)
        {
            int new_socket = acceptConnection(socket, address);
            response(new_socket);
        }
        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
}
