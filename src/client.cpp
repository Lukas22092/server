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

void Client::listen_blocking(){
    boost::system::error_code ec;
    std::cout << "starting reading\n";
    for(;;){
            size_t len = socket.read_some(boost::asio::buffer(buf), ec);          
              std::cout << buf.size();
            if (ec == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (ec)if (ec == boost::asio::error::eof)

                throw boost::system::system_error(ec); // Some other error.


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