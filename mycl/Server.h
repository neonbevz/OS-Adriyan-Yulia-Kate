#ifndef MYCL_SERVER_H
#define MYCL_SERVER_H

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

std::string makeDateString();

std::string makeTimeString();

int countWords(std::string s);

#endif //MYCL_SERVER_H
