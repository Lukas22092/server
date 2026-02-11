#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include "client.hpp"


Client::Client(boost::asio::io_context& io_context) 
    :resolver(io_context), 
     socket(io_context) 
     {
        try
        {
            tcp::resolver::results_type endpoints =
            resolver.resolve("localhost", "1234");
            boost::asio::connect(socket, endpoints);
            std::cout << "connected\n";
        }
        catch(const boost::system::system_error& e){
            std::cerr << "[LINE " << __LINE__ << "]" << e.what();
            throw;
        }

        for(;;){
            size_t len = socket.read_some(boost::asio::buffer(buf), error);
            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.
        }
     }