#include "includes.h"
#include "Matrix.h"
#define PRIME 73

// int connfd;

void func(int sockfd)
{
    int buff[MAX];
    int n = 0;
    int size[4];
    int prime;
    prime = PRIME;
    std::cout << "Enter matrix dimensions" <<  std::endl;
    while(n != 4)
    {
        bzero(buff, MAX);
        std::cin >> buff[0];
        if (buff[0] != ' ') {
            write(sockfd, buff, sizeof(buff));
            size[n] = buff[0];
            n++;
        }
    }

    if (size[1] != size[2])
    {
        throw std::runtime_error("matrix dimensions incompatible");
    }
    
    // std::cout << "Enter modulo" <<  std::endl;
    // std::cin >> prime;
    // buff[0] = prime;
    // write(sockfd, buff, sizeof(buff));

    std::cout << "Enter first matrix:" << std::endl;
    Matrix A {size[0], size[1], prime};
    std::cin >> A;
    A.Send(sockfd);

    Matrix B {size[2], size[3], prime};
    std::cout << "Enter second matrix:" << std::endl;
    std::cin >> B;
    B.Send(sockfd);

    Matrix C{size[0], size[3], prime, sockfd};

    std::cout << "Product" << std::endl;
    std::cout << C;
}

void signalHandler(int signum){
    std::cout << "\nInterrupt signal (" << signum << ") received.\n";
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // close(connfd);
    close(sockfd);
    exit(signum);
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    try {
        // socket create and verification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd == -1){
            throw std::runtime_error("socket creation failure\n");
        }
    }
    catch (std::exception& ex){
        std::cout << "Error: " << ex.what();
    }

    std::cout << "Socket successfully created" << std::endl;
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    try {
        connfd = connect(sockfd, (SA*)&servaddr, sizeof(servaddr));
        if (connfd < 0){
            throw std::runtime_error("connection with server failed\n");
        }
    }
    catch (std::exception& ex){
        std::cout << "Error: " << ex.what();
    }
    
    std::cout << "Connection established" << std::endl;
    signal(SIGINT, signalHandler);

    while(1){
        try{
            // function for chat
            func(sockfd);
        }
        catch (std::exception& ex){
            std::cout << "Error: " << ex.what();
        }
    }
    // close the socket
    close(sockfd);
}
