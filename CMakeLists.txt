cmake_minimum_required(VERSION 3.10)
project(websocket)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(socket
    src/main.cpp
    src/foo.cpp
)

add_executable(client
    src/client.cpp
)

target_link_libraries(socket PRIVATE Boost::boost Boost::system)
target_link_libraries(client PRIVATE Boost::boost Boost::system)

target_include_directories(socket PRIVATE include)
target_include_directories(client PRIVATE include)