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


class tcp_connection : public std::enable_shared_from_this<tcp_connection>
{
    public:
    ///create a new tcp connection instance.
    static std::shared_ptr<tcp_connection> create(boost::asio::io_context& io_context);

    ///constructor sets the socket
    tcp_connection(boost::asio::io_context& io_context);
   
    ///starts the tcp server
    void  start();    

    ///wait for users to send a message
    void start_reading();

    template<typename T, typename SendableData>
    void send_to_user(const T& message, const SendableData& to_send) {
            std::cout << "initializing write\n";
            auto data_to_send = std::make_shared<player_data>(message);
            auto data_type = std::make_shared<SendableData>(to_send);

            //first send the type we want to send so the user knows how to unpack it.
            boost::asio::async_write(socket_, boost::asio::buffer(data_type.get(), sizeof(to_send)),
                    [self = shared_from_this(), to_send](const boost::system::error_code& error, size_t bytes_transferred) {
                        self->start_reading();
                    });
            //now, send the data
            /*
            boost::asio::async_write(socket_, boost::asio::buffer(data_to_send.get(), sizeof(message)),
                [self = shared_from_this(), data_to_send](const boost::system::error_code& error, size_t bytes_transferred) {
                    self->start_reading();
                });
            std::cout << "sent position : "<< message.position << "\n";
            std::cout << "sent player_ID : "<< static_cast<int32_t>(message.player_ID) << "\n";
              */
        }
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