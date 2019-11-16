#include "includes.h"
#include "Matrix.h"
#include <vector>
#include <iomanip>


void func(int sockfd){
    int buff[MAX];
    int size[4];
    Matrix A, B, C;

    for (int i = 0; i < 4; i++)		//accept matrix sizes
    {
        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));
        size[i] = buff[0];
    }
    if (size[1] != size[2])
    {
        printf("Dimensions are incompatible\n");
    }

    else
    {
        A = {size[0], size[1], sockfd};
        B = {size[2], size[3], sockfd};
    }
    C = Mult(A, B);
    C.Send(sockfd);
}

int main()
{
    int sockfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    // Accept the data packet from client and verification
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) {
        printf("server acccept failed...\n");
        exit(0);
    }
    else
        printf("server acccept the client...\n");

    // Function for chatting between client and server
    func(connfd);

    // After chatting close the socket
    close(sockfd);
}
