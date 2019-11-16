#include "includes.h"

using namespace std;

void print(vector<vector<type>> A) {		//function to print two-dimensional vectors
    int n = A.size();
	int m = A[0].size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cout << A[i][j] << "\t";
        }
        cout << "\n";
    }
}

void func(int sockfd)
{
	int buff[MAX];
	int n = 0;
	int size[4];
	vector<vector<type>> C;

	printf("Enter matrix dimensions:\n");
	while(n != 4)
	{
		bzero(buff, MAX);
		
		// buff[0] = getchar();
		scanf("%d", &buff[0]);
		if (buff[0] != ' ')
		{
			write(sockfd, buff, sizeof(buff));
			size[n] = buff[0];
			n++;
		}
	}

	printf("Enter first matrix:\n");
	for(int j = 0; j < size[0]; j++){
		for(int i = 0; i < size[1]; i++){
			cin >> buff[i];
		}
		write(sockfd, buff, sizeof(buff));
	}

	printf("Enter second matrix:\n");
	for(int j = 0; j < size[2]; j++){
		for(int i = 0; i < size[3]; i++){
			cin >> buff[i];
		}
		write(sockfd, buff, sizeof(buff));
	}

	printf("Product:\n");
	for (int count = 0; count < size[0]; count++)		//accept matrix product
	{
		vector<type> temp(size[1]);
		bzero(buff, MAX);
		read(sockfd, buff, sizeof(buff));
		for (int i = 0; i < size[3]; i++)
		{
			temp[i] = buff[i];
		}
		C.push_back(temp);
	}
	print(C);
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

