cmake_minimum_required(VERSION 3.10)
project(CPPWebServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(webserver src/main.cpp src/SocketHandle.cpp)