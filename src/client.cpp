#include "client.hpp"
#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include <atomic>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

using boost::asio::ip::tcp;

termios original_termios;
bool connected{true};

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &original_termios);
    termios raw = original_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

int main() {

    signal(SIGPIPE, SIG_IGN);

    enableRawMode();
    atexit(disableRawMode);

    try {
        boost::asio::io_context io;
        tcp::socket socket(io);

        socket.connect(
            tcp::endpoint(
                boost::asio::ip::make_address("127.0.0.1"), 1234
            )
        );

        std::cout << "Connected to server. please enter a number (1) or (2)\n";


        // Send every keypress immediately
        while (connected) {
            char c;
            if (read(STDIN_FILENO, &c, 1) == 1) {
                boost::system::error_code ec;
                boost::asio::write(socket, boost::asio::buffer(&c, 1), ec);

                if (ec) {
                    connected = false;
                    break;
                }
            }
        }

        socket.close();
    }
    catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
    }
}
