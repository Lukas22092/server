add_executable(socket main.cpp)

target_link_libraries(socket foo.cpp PRIVATE include)

target_link_libaries(game_data game_data.cpp client.cpp PRIVATE include)