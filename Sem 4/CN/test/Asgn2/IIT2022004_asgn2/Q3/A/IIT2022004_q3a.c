#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> // read(), write(), close()
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

// Function designed for chat between client and server. 
char func1(int connfd) 
{ 
    char buff[MAX]; 
    int n; 
    char c;
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 

        // read the message from client and copy it in buffer 
        read(connfd, buff, sizeof(buff)); 
        // print buffer which contains the client contents 
        printf("From client 1: %s\t", buff); 
        
        n = 0; 
        // copy server message in the buffer 
        

        // and send that buffer to client 
        // write(connfd, "Received character", sizeof(buff)); 

        // if msg contains "Exit" then server exit and chat ended. 
        
        return buff[0];
    } 
} 
void func2(int connfd,char c) 
{ 
    char buff[MAX]; 
    int n; 
    
    // infinite loop for chat 
    for (;;) { 
        bzero(buff, MAX); 
        buff[0]=c+1;
        
        

        // and send that buffer to client 
        write(connfd, buff, sizeof(buff)); 

        // if msg contains "Exit" then server exit and chat ended. 
        
    } 
} 

// Driver function 
int main() 
{ 
    int sockfd, connfd, len; 
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

    // Accept the 1st client data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server accept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server accept the client...\n"); 

    // Function for chatting between client and server 
    char c=func1(connfd); 
    
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server accept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server accept the client...\n"); 
    func2(connfd,c);
    // After chatting close the socket 
    close(sockfd); 
}
