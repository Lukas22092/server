#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <boost/asio.hpp>
#include <array>
#include <vector>
#include <iostream>
#include "game_data.hpp"

using boost::asio::ip::tcp;


class Client
{
    private:
    tcp::resolver resolver;
    tcp::socket socket;
    std::vector<player_data> buf;


    public:
    Client(boost::asio::io_context& io_context);
    void listen_blocking();
    void connect();

    ~Client(){}
};


#endif