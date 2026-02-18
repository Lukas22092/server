#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

#include<stdint.h>
#include<iostream>

template<typename T>
std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream, const T& e)
{
    return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

enum class SendableData
{
    Position,
    Color,
};


struct player_data{ 
    int8_t player_ID = 42;
    int32_t position = 200;
    ~player_data(){std::cout << "destructor ran\n";}
};

void say_data(const player_data& data);



#endif
