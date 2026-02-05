/*
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
    */
#include <iostream>
#include <span>
using namespace std;

int main()
{
    int arr[] = { 1, 2, 3, 4, 5 };

    // Create a span of int of array
    span<int> span_arr(arr);

    for (const auto& num : span_arr) {
        cout << num << " ";
    }
    return 0;
}