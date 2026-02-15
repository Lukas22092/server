#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include "client.hpp"


Client::Client(boost::asio::io_context& io_context) :
    resolver(io_context), 
    socket(io_context) 
    {}  
     
void Client::connect(){
    try{
        boost::asio::connect(socket, resolver.resolve("localhost", "1234"));
        }
    catch(const boost::system::system_error& e){
        std::cerr << "[LINE " << __LINE__ << ", FILE "<< __FILE_NAME__ << "] connection refused! maybe you forgot to start the server";
        return;
    }
}
void Client::listen_blocking() {
    boost::system::error_code ec;
    
    buf.resize(10); 

    for (;;) {
        size_t len = socket.read_some(
            boost::asio::buffer(buf, buf.size() * sizeof(player_data)), 
            ec
        );
        if (ec) break;
        size_t num_structs = len / sizeof(player_data);

        for (size_t i = 0; i < num_structs; ++i) {

            std::cout << "Received Player ID: " << static_cast<int32_t>(buf[i].player_ID) 
                      << " Position: " << buf[i].position << "\n";
        }
    }
}

int main() {
    try {
        boost::asio::io_context io_context;
        Client client(io_context);
        client.connect();
        client.listen_blocking(); 
    } catch (boost::system::system_error& e) 
    {std::cerr << "error\n";}
    return 0;
}