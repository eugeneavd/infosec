#include "includes.h"
#include "Matrix.h"

void func(int sockfd)
{
    int buff[MAX];
    int n = 0;
    int size[4];

    printf("Enter matrix dimensions:\n");
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

    printf("Enter first matrix:\n");
    Matrix A {size[0], size[1]};
    std:: cin >> A;
    A.Send(sockfd);

    Matrix B {size[2], size[3]};
    printf("Enter second matrix:\n");
    std::cin >> B;
    B.Send(sockfd);

   Matrix C{size[0], size[3], sockfd};

    printf("Product:\n");
    std::cout << C;
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // socket create and varification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    // function for chat
    func(sockfd);

    // close the socket
    close(sockfd);
}
