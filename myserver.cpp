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

vector<vector<type>> product(vector<vector<type>> A, vector<vector<type>> B){			//function to compute matrix product
	int n = A.size();
	int m = A[0].size();
	int l = B[0].size();
	vector<vector<type>> C(n);

	for (int i = 0; i < n; i++)
	{
		C[i].resize(l);
	}
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < l; j++){
			for(int k = 0; k < m; k++){
				C[i][j] += A[i][k]*B[k][j];
			}
		}
	}

	return C;
}

void func(int sockfd){
    int buff[MAX];
    int n;
    int size[4];
	vector<vector<type>> A;
	vector<vector<type>> B;
	vector<vector<type>> C;

    for (int i = 0; i < 4; i++)		//accept matrix sizes
    {
        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));
        // size[i] = atoi(buff);
		size[i] = buff[0];
    }

    // printf("Matrix dimensions:\n");
    // for (int i = 0; i < 4; i++)
    // {
    //     printf("%d\t", size[i]);
    // }
    // printf("\n");

	if (size[1] != size[2])
	{
		printf("Dimensions are incompatible\n");
	}

	else
	{
		for (int count = 0; count < size[0]; count++)			//accept first matrix
		{
			vector<type> temp(size[1]);
			bzero(buff, MAX);
			read(sockfd, buff, sizeof(buff));
			for (int i = 0; i < size[1]; i++)
			{
				temp[i] = buff[i];
			}
			A.push_back(temp);
		}

		for (int count = 0; count < size[2]; count++)			//accept second matrix
		{
			vector<type> temp(size[3]);
			bzero(buff, MAX);
			read(sockfd, buff, sizeof(buff));
			for (int i = 0; i < size[3]; i++)
			{
				temp[i] = buff[i];
			}
			B.push_back(temp);
		}
		
	}
	// cout << "First matrix\n";
	// print(A);
	// cout << "Second matrix\n";
	// print(B);
	// cout << "Product\n";
	C = product(A, B);
	// print(C);
	
	for(int i = 0; i < size[0]; i++){			//send product
		for(int j = 0; j < size[3]; j++){
			buff[j] = C[i][j];
		}
		write(sockfd, buff, sizeof(buff));
	}
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
