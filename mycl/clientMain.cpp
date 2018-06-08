#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstdlib>
#include <strings.h>
#include <boost/asio/write.hpp>
#include <iostream>
#include <bitset>

int main(int argc, char *argv[])
{
    int sockfd, portno;
    long n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 4) {
        std::cerr << "usage: " << argv[0] << " hostname port (d|t|h|m [message])" << std::endl;
        exit(1);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        std::cerr << "Error opening socket" << std::endl;
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        std::cerr << "Error - host not found" << std::endl;
        exit(2);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        std::cerr << "Connection error" << std::endl;

    std::string param = argv[3];

    if (param == "d" || param == "t" || param == "h") {
        n = write(sockfd, param.c_str(), strlen(argv[3]));
    }
    else if (param == "m") {
        n = write(sockfd, param.c_str(), strlen(argv[3]));
    } else {
        return 3;
    }
    if (n < 0)
        std::cerr << "Error writing to socket" << std::endl;


    if (param == "m") {
        std::string message;
        std::cout << "Enter the message:" << std::endl;
        getline (std::cin, message);

        uint16_t len = message.size();
        std::string bitLen = std::bitset< 16 >(len).to_string();

        n = write(sockfd, bitLen.c_str(), strlen(bitLen.c_str()));
        if (n < 0)
            std::cerr << "Error writing to socket" << std::endl;

        n = write(sockfd, message.c_str(), strlen(message.c_str()));
    }

//    printf("Please enter the message: ");
//    bzero(buffer,256);
//    fgets(buffer,255,stdin);
//    n = write(sockfd,buffer,strlen(buffer));

    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0)
        std::cerr << "ERROR reading from socket" << std::endl;
    std::cout << buffer << std::endl;
    return 0;
}