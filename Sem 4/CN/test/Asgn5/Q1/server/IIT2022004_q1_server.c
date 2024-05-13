#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024


void send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp)!=NULL)
    {
        if(send(sockfd, data, sizeof(data), 0)== -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
        bzero(data, SIZE);
    }
}

int main ()
{
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        perror("Error in socket");
        exit(1);
    }
     printf("Server socket created. \n");

     server_addr.sin_family = AF_INET;
     server_addr.sin_port = port;
     server_addr.sin_addr.s_addr = inet_addr(ip);

     e = bind(sockfd,(struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e<0)
     {
         perror("Error in Binding");
         exit(1);
     }
     printf("Binding Successfull.\n");

     e = listen(sockfd, 10);
     if(e==0)
     {
         printf("Listening...\n");
     }
     else 
     {
         perror("Error in Binding");
         exit(1);
     }
     addr_size = sizeof(new_addr);
     new_sock = accept(sockfd,(struct sockaddr*)&new_addr, &addr_size);
     char filename_buff[50];
     recv(new_sock,filename_buff,50,0);
     FILE *fptr;
     fptr = fopen(filename_buff, "r");
     
     send_file(fptr,new_sock);

     printf("Data sent successfully");
}
