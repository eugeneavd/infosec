#include "includes.h"
#include "Matrix.h"

void func(int sockfd)
{
    int buff[MAX];
    int n = 0;
    int size[4];

    std::cout << "Enter matrix dimensions" << std::endl;
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

    std::cout << "Enter first matrix:" << std::endl;
    Matrix A {size[0], size[1]};
    std:: cin >> A;
    A.Send(sockfd);

    Matrix B {size[2], size[3]};
    std::cout << "Enter second matrix:" << std::endl;
    std::cin >> B;
    B.Send(sockfd);

    Matrix C{size[0], size[3], sockfd};

    std::cout << "Product" << std::endl;
    std::cout << C;
}

void VerifySocket(int sockfd){
    if (sockfd == -1)
    {
        std::cout << "socket creation failure" << std::endl;
        throw std::runtime_error("socket creation failure");
    }
}

void VerifyConnection(int sockfd, struct sockaddr_in servaddr){
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
    {
        std::cout << "connection with server failed" << std::endl;
        throw std::runtime_error("connection with server failed");
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    try {
        // socket create and verification
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        VerifySocket(sockfd);
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

    // connect the client socket to server socket
    // if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
    //     std::cout << "Connection with server failed" << std::endl;
    //     // exit(0);
    //     // throw "connection failure";
    //     throw std::exception();
    // }
    // else
    try {
        VerifyConnection(sockfd, servaddr);
    }
    catch (std::exception& ex){
        std::cout << "Error: " << ex.what();
    }
    
    std::cout << "Connection established" << std::endl;

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}
