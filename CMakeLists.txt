cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0167 NEW) #surpresses warning when compiling
project(websocket)
set (CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost REQUIRED COMPONENTS filesystem json)
find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(OpenSSL REQUIRED)

add_executable(socket
    src/main.cpp
    src/foo.cpp
)

add_executable(client
    src/client.cpp
    )

target_include_directories(client PRIVATE include)

target_include_directories(socket PRIVATE include)

target_link_libraries(client PRIVATE  OpenSSL::SSL OpenSSL::Crypto Boost::json Boost::filesystem)
target_link_libraries(socket PRIVATE  OpenSSL::SSL OpenSSL::Crypto Boost::json Boost::filesystem)
