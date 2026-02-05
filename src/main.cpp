
#include "foo.hpp"
#include <termios.h>


int main() {

    try {
        boost::asio::io_context io_context;
        tcp_server server(io_context);
        
        std::cout << "Server started running" << std::endl;
        io_context.run();
        std::cout << "finished running" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "exception caught: " << e.what() << std::endl;
    }

}
 