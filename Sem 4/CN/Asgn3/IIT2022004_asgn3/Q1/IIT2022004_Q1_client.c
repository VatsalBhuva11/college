
#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>
#include <unistd.h> // read(), write(), close()
#define MAX 100
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    int key = 0;
    int n;
    bzero(buff, sizeof(buff));
    printf("Enter the key : ");
    n = 0;
    // first, read the key from the client into the client buffer
    scanf("%s", buff);
    
    // send that key (buffer) to the server
    int ct = send(sockfd, buff, sizeof(buff), 0);
	
	// empty that buffer to read the output received from the server
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("From Server : \n%s", buff);
    
    // post processing (deletion of memory)
    bzero(buff, sizeof(buff));
    
    // reading the read
    name(sockfd, buff, sizeof(buff));
    printf("%s", buff);
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // creating a socket in the client side
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));
    
    // storing the server socket information in the servaddr struct
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    
    // connecting to the servaddr, and the server socket info stored in sockfd
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");
    func(sockfd);
    close(sockfd);
}
