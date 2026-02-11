cmake_minimum_required(VERSION 3.28)
project(websocket)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED COMPONENTS system)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(socket
    src/main.cpp
    src/game_data.cpp
    src/server.cpp
)
add_executable(client
    src/client.cpp
)

target_link_libraries(client PRIVATE Boost::boost Boost::system  Qt6::Widgets)
target_link_libraries(socket PRIVATE Boost::boost Boost::system  Qt6::Widgets)

target_include_directories(client PRIVATE include)
target_include_directories(socket PRIVATE include)
