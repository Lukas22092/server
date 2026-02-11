#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include<stdint.h>
#include<iostream>

struct player_data{
    int8_t player_ID = 42;
    int32_t position = 200;
    ~player_data(){std::cout << "destructor ran\n";}
};

void say_data(const player_data& data);



#endif
