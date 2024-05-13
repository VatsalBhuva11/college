#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <signal.h>

#define MAXPENDING 5
#define BUFFSIZE 2048
#define MAX 2048
void error_handler(char *mess) 
{
    perror(mess);
    exit(1);
}

void tokenizer(char inputBuffer[], char *args[], int *background) 
{
    const char s[4] = " \t\n";
    char *token;
    token = strtok(inputBuffer, s);
    int i = 0;
    while( token != NULL)
    {
        args[i] = token;
        i++;
        //printf("%s\n", token);
        token = strtok(NULL,s);
    }
    args[i] = NULL;
}

void serve_client(int sock){

    char buffer[BUFFSIZE];
    int received = -1;
    char data[MAX];
    memset(data,0,MAX);

    while(1) { 
        data[0] = '\0';
        if((received = recv(sock, buffer,BUFFSIZE,0))<0){

            error_handler("Failed");
        }

        buffer[received] = '\0';

        strcat (data,  buffer);
        if (strcmp(data, "exit")==0) 
            exit(0);
        puts (data);
        char *args[100];
        tokenizer(data,args,0);
        int pipefd[2],lenght;

        if(pipe(pipefd)){
            error_handler("Failed to create pipe");
        }

        pid_t pid = fork();
        char path[MAX];

        if(pid==0){
            close(1); 
            dup2(pipefd[1],1); 
            close(pipefd[0]); 
            close(pipefd[1]); 
            system(args[0]); 
        }
        else
            if(pid>0){
                close(pipefd[1]);
                memset(path,0,MAX);
                while((lenght=read(pipefd[0],path,MAX-1))){
                    printf("Data read so far %s\n", path);
                    if(send(sock,path,strlen(path),0) != strlen(path) ){
                        error_handler("Failed");
                    }
                    fflush(NULL);
                    printf("Data sent so far %s\n", path);
                memset(path,0,MAX);
                }
                close(pipefd[0]);      
            }
            else{
                printf("Error !\n");
                exit(0);
            }
    }
/*
    if (strcmp (data, "exit")==0)
    {
        exit (1);
    }
    printf("Closing socket\n");
    close(sock);
*/
}

int main(int argc, char const *argv[])
{
    int serversock,clientsock;
    struct sockaddr_in echoserver, echoclient;
    unsigned int clientlen = sizeof(echoclient);
    signal(SIGPIPE, SIG_IGN); 
    if((serversock = socket(PF_INET, SOCK_STREAM,IPPROTO_TCP))<0){
        error_handler("Failed");
    }
    memset(&echoserver,0,sizeof(echoserver));
    echoserver.sin_family = AF_INET;
    echoserver.sin_addr.s_addr= htonl(INADDR_ANY);
    echoserver.sin_port = htons(atoi(argv[1]));

    if(bind(serversock, (struct sockaddr *) & echoserver,sizeof(echoserver))<0){
        error_handler("Failed");
    }
    if(listen(serversock,MAXPENDING)<0){
        error_handler("Failed");
    }
    struct hostent *host;
    while(1)
    {
        if((clientsock = 
            accept(serversock,(struct sockaddr *) &echoclient,
                                &clientlen))<0){
            error_handler("Failed");
        }
        char ipv4addr[sizeof(struct in_addr)];
        struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&echoclient;
        struct in_addr ipAddr = pV4Addr->sin_addr;
        char address[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ipAddr, address, INET_ADDRSTRLEN );
        inet_pton(AF_INET, address, ipv4addr);  
        host = gethostbyaddr(&ipv4addr, sizeof(ipv4addr), AF_INET);
	    if(host ==NULL){
		    printf("Error AHAHA:%s\n", hstrerror(h_errno));
	    }
	    else{
	    	printf("\nRequest from host : %s\n",host->h_name);
	    }
        fprintf(stdout, "Client connected: %s\n",
                        inet_ntoa(echoclient.sin_addr));
        fprintf(stdout,"Message from client:");
        serve_client(clientsock);        
    }

    return 0;
}
