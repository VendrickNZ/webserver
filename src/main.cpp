#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    int addrlen = sizeof(address);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(3000);

    bind(server_fd, (sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Server listening on port 3000\n";

    while (true) {
        int new_socket = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);
        
        char buffer[30000] = {0};
        read(new_socket, buffer, 30000);
        std::cout << "Request received:\n" << buffer << "\n";

        const char* response =
            "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 48\n\n"
            "<html><body><h1>Hello World!</h1></body></html>";

        write(new_socket, response, strlen(response));
        close(new_socket);
    }

    close(server_fd);
    return 0;
}
