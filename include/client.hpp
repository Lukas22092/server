#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <boost/asio.hpp>
#include <array>
#include <iostream>


using boost::asio::ip::tcp;


class Client
{
    private:
    tcp::resolver resolver;
    tcp::socket socket;
    std::array<char, 128> buf;
    boost::system::error_code error;


    public:
    Client(boost::asio::io_context& io_context);

    ~Client(){}
};


#endif