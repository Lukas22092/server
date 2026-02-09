#ifndef server_HPP
#define server_HPP
#include <memory>
#include <iostream>
#include <boost/asio.hpp>
#include <set>
#include <vector>
#include "game_data.hpp"

using boost::asio::ip::tcp;
class tcp_connection;

class Tron{
    std::set<std::shared_ptr<tcp_connection>> connections_; 
};

class tcp_connection : public std::enable_shared_from_this<tcp_connection>
{
    public:
    ///create a new tcp connection instance.
    static std::shared_ptr<tcp_connection> create(boost::asio::io_context& io_context);

    ///constructor sets the socket
    tcp_connection(boost::asio::io_context& io_context);

    ///starts the tcp server
    void start();

    ///wait for users to send a message
    void start_reading();

    ///send a message to a connected user
    void send_to_user(const std::vector<player_data>& message);

    //returns the socket object, used for using it in the tcp_server class.
    tcp::socket& socket();


    ///member variables: 
    tcp::socket socket_; //each connection has a socket,
    std::array<char, 1024> buffer_; //each connection has a receiving buffer
    int user_id = -1;


};
class tcp_server : public std::enable_shared_from_this<tcp_server> 
{
    public:
        tcp_server(boost::asio::io_context& io_context);

private:
    void start_accept(); 

    void handle_accept(std::shared_ptr<tcp_connection> new_connection, const boost::system::error_code& error) {
        if (!error) {
            new_connection->start();
        }
        start_accept();
    }

    boost::asio::io_context& io_context_;
    tcp::acceptor acceptor_;


};


#endif