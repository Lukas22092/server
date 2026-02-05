add_executable(socket main.cpp)

target_link_libraries(socket foo.cpp PRIVATE include)
target_link_libaries(client client.cpp PRIVATE include)