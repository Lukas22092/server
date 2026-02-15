#include "server.hpp"

tcp_connection::tcp_connection(boost::asio::io_context& io_context) : socket_(io_context) {}


std::shared_ptr<tcp_connection> tcp_connection::create(boost::asio::io_context& io_context) {
    return std::make_shared<tcp_connection>(io_context);
    }

void tcp_connection::start_reading() {
        socket_.async_read_some(boost::asio::buffer(buffer_),
            [self = shared_from_this()](boost::system::error_code ec, std::size_t length) {
                if(ec) std::cout << "client disconnected\n";
                else {

            std::string request(self->buffer_.data(), length);

            request.erase(request.find_last_not_of(" \n\r\t") + 1);

            if (request.empty()) {
                self->start_reading();
                return;
            }

            if (self->user_id == -1) {
                try {
                    self->user_id = std::stoi(request);
                    std::cout << "User authenticated with ID: " << self->user_id << "\n";
                    //self->send_to_user("ID Accepted. Welcome, Player " + request + "\n");
                } catch (...) {
                    std::cout << "Invalid ID received: " << request << "\n";
                    //self->send_to_user("Error: ID must be a number.\n");
                }
            } else {
                std::cout << "Message from " << self->user_id << ": " << request << "\n";
                
            }

            self->start_reading();
        }
            
            });
        };
    

boost::asio::ip::tcp::socket& tcp_connection::socket(){return socket_;};

//might be possible that this wont work as a return right after calling -> message might be destroyed as the calling
//function will be taken off the stack!
void tcp_connection::send_to_user(const player_data& message) {
        std::cout << "initializing write\n";
        auto saved_data = std::make_shared<player_data>(message);

        boost::asio::async_write(socket_, boost::asio::buffer(saved_data.get(), sizeof(message)),
            [self = shared_from_this(), saved_data](const boost::system::error_code& error, size_t bytes_transferred) {
                self->start_reading();
            });
        std::cout << "sent position : "<< message.position << "\n";
        std::cout << "sent player_ID : "<< static_cast<int32_t>(message.player_ID) << "\n";

    }



void tcp_connection::start() {
        socket_.set_option(boost::asio::ip::tcp::no_delay(true));
        std::cout << std::string_view("someone connected\n");
        
        player_data data = player_data();
        send_to_user(data);
    }


tcp_server::tcp_server(boost::asio::io_context& io_context)
            : io_context_(io_context),
            acceptor_(io_context, tcp::endpoint(tcp::v4(), 1234)) {
            start_accept();
        }

void tcp_server::start_accept(){
        std::shared_ptr<tcp_connection> new_connection = tcp_connection::create(io_context_);

        acceptor_.async_accept(new_connection->socket(),
            std::bind(&tcp_server::handle_accept, this, new_connection,
                boost::asio::placeholders::error));
    }
