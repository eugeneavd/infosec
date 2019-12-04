#include "includes.h"
#include "Matrix.h"
#include <iostream>
#include <vector>
#include <iomanip>
#define PRIME 73


void func(int sockfd){
    int buff[MAX];
    int size[4];

    for (int i = 0; i < 4; i++)		//accept matrix sizes
    {
        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));
        size[i] = buff[0];
    }
    if (size[1] != size[2])
    {
        throw std::runtime_error("matrix dimensions incompatible");
    }
    auto A = Matrix(size[0], size[1], PRIME, sockfd);
    auto B = Matrix(size[2], size[3], PRIME, sockfd);
    auto C = A * B;
    C.Send(sockfd);
}

int main()
{
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;

    try{
        // socket create and verification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1) {
            throw std::runtime_error("socket creation failure\n");
        }
    }
    catch(const std::exception& ex){
        std::cout << "Error: " << ex.what();
    }
    std::cout << "Socket created successfully" << std::endl;
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);


    // Binding newly created socket to given IP and verification
    try{
        if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
            throw std::runtime_error("Socket bind failed");
        }
    }
    catch(const std::runtime_error& ex){
        std::cout << "Error: " << ex.what();
    }
    std::cout << "Socket successfully binded" << std::endl;

    // Now server is ready to listen and verification
    try{
        if ((listen(sockfd, 5)) != 0) {
            throw std::runtime_error("Listen failed");
        }
    }
    catch(const std::runtime_error& ex){
        std::cout << "Error: " << ex.what();
    }
    std::cout << "Server listening.." << std::endl;
    len = sizeof(cli);

    try{
        // Accept the data packet from client and verification
        connfd = accept(sockfd, (SA*)&cli, &len);
        if (connfd < 0) {
            throw std::runtime_error("Server acccept failed");
        }
    }
    catch(const std::runtime_error& ex){
        std::cout << "Error: " << ex.what();
    }
    std::cout << "Server acccepts the data from client" << std::endl;

    try{
        // Function for chatting between client and server
        func(connfd);
    }
    catch (std::exception& ex){
        std::cout << "Error: " << ex.what();
    }
    // After chatting close the socket
    close(sockfd);
}
