#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

void write_file(int sockfd,char * filename)
{
    int n; 
    FILE *fp;
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if(fp==NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }
    while(1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if(n<=0)
        {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;
    
}

int main(int argc,char *argv[])
{

    // $./client [server_address] [port_number] [file_name.txt] [recv_file_name.txt]

    if(argc != 5) {
        printf("\nInvalid Number of Arguments\n");
        exit(-1);
    }
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    int sockfd;
    struct sockaddr_in server_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
     printf("[+]Server socket created. \n");

     server_addr.sin_family = AF_INET;
     server_addr.sin_port = htons(atoi(argv[2]));
     server_addr.sin_addr.s_addr = inet_addr(argv[1]);

     e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
     if(e == -1)
     {
         perror("[-]Error in Connecting");
         exit(1);
     }
     printf("[+]Connected to server.\n");
     
     send(sockfd,argv[3],50,0);
     write_file(sockfd,argv[4]);
     printf("[+] File data received successfully. \n");
     close(sockfd);
     printf("[+]Disconnected from the server. \n");
     return 0;

}
