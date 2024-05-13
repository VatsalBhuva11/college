
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
// #include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> // read(), write(), close()
#include "prtcl.h"
#define MAX 80
#define PORT 8080
#define SA struct sockaddr

int main()
{
    int sockfd, connfd, len, new_sockfd;
    struct sockaddr_in servaddr, cli;
    char *c;
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
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");
    if ((listen(sockfd, 5)) != 0)
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
        printf("Server listening..\n");
    len = sizeof(cli);

    FILE *fptr = fopen("./database.txt", "r");
    char buff[MAX];
    while (1)
    {
        int key;
        // char buff[50];
        new_sockfd = accept(sockfd, (struct sockaddr *)&cli, &len);

        if (new_sockfd == -1)
            printf("accepting connection");
        printf("server: got connection from %s port %d\n",
               inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        // CHANGED FROM LAST QUESTION

        char temp_key[50];
        char cur_name[50];
        char buff[200];
        char data[200];
        
        // buff will now contain "type + message + ETR"
        int ct = recv(new_sockfd, &buff, sizeof(buff), 0);
        
        // received data from client into data. only the key is obtained (not the type)
        getReqData(buff, data, 200);
        int flag = 0;

        while ((fscanf(fptr, "%s %s", temp_key, cur_name)) != EOF)
        {
        	// the type is obtained using the getReqType function by getting the buff[0] value
            if (strcmp(((getReqType(buff) == 1) ? cur_name : temp_key), data) == 0)
            {
				// send the response to the client
                ddres_send(new_sockfd, ((getReqType(buff) == 1) ? temp_key : cur_name), 50);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            ddres_send(new_sockfd, "\nSorry entry not found\n", 100);

        // END CHANGE

        rewind(fptr);
        fseek(fptr, 0, SEEK_SET);
        close(new_sockfd);
    }

    fclose(fptr);
    close(sockfd);
}
