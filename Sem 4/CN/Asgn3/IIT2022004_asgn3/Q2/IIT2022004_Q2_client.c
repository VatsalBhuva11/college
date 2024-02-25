
#include <arpa/inet.h> // inet_addr()
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // bzero()
#include <sys/socket.h>

#include <unistd.h> // read(), write(), close()

#include "prtcl.h"
#define MAX 100
#define PORT 8080
#define SA struct sockaddr
void func(int sockfd)
{
    char buff[MAX];
    char data[MAX];
    int key = 0;
    int n;

    bzero(buff, sizeof(buff));
    int type;
    printf("Enter the type of data sent (0 for number, 1 for name) : ");
    scanf("%d", &type);
    printf("\nEnter the key : ");
    n = 0;
    scanf("%s", buff);
    int ct = ddreq_send(sockfd, buff, sizeof(buff), type);
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    printf("From Server : \n%s", buff);
    bzero(buff, sizeof(buff));
    read(sockfd, buff, sizeof(buff));
    getResData(buff, data, 100);
    printf("\n%s\n", data);
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

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
