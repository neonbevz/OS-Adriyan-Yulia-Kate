#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <bitset>

#include "Server.h"

using boost::asio::ip::tcp;

int main(int argc, char *argv[])
{
    unsigned short port = 13;
    if (argc > 1) port = atoi(argv[1]);
    std::cout << "Server starting..." << std::endl << "Port: " << port << std::endl;
    try
    {
        boost::asio::io_service io_service;

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
        for (;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            boost::asio::streambuf sb;
            boost::system::error_code ec;
//            boost::asio::read_until(socket, sb, "\n", ec);
            boost::asio::read(socket, sb, boost::asio::transfer_exactly(1), ec);
//            std::cout << "received: '" << &sb << "'\n";

            if (ec) {
                std::cout << "status: " << ec.message() << std::endl;
            }

            std::ostringstream ss;
            ss << &sb;

            sb.consume(10);
            std::string s = ss.str();

            std::string message;

            if (s[0] == 'd') {
                std::cout << "d" << std::endl;
                message = makeDateString();
            } else if (s[0] == 't') {
                std::cout << "t" << std::endl;
                message = makeTimeString();
            } else if (s[0] == 'h') {
                std::cout << "h" << std::endl;
                message = "Hello, socket\n";
            } else if (s[0] == 'm') {
                std::cout << "m" << std::endl;

                while(!boost::asio::read(socket, sb, boost::asio::transfer_exactly(16), ec)) {}

                std::ostringstream bitSs;
                bitSs << &sb;
                sb.consume(20);

                std::string bitStr = bitSs.str();
                uint16_t len = std::stoi(bitStr, nullptr, 2);

                while(!boost::asio::read(socket, sb, boost::asio::transfer_exactly(len), ec)) {}

                std::ostringstream inMessageStream;
                inMessageStream << &sb;
                sb.consume(len + 5);

                std::string inMessage = inMessageStream.str();

                int words = countWords(inMessage);

                message = std::to_string(words) + " words received";
            }

            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
#pragma clang diagnostic pop
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}