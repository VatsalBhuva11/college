#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
struct message{
    char c;
    int d;
    float f;
};
typedef struct message mess;
int main(void){
    int socket_desc;
    struct sockaddr_in server_addr, client_addr,client_addr2;
    char server_message[100];
    mess client_message;
    int client_struct_length = sizeof(client_addr);
    
    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(&client_message, '\0', sizeof(client_message));
    
    // Create UDP socket:
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if(socket_desc < 0){
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created successfully\n");
    
    // Set port and IP:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2001);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Bind to the set port and IP:
    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        printf("Couldn't bind to the port\n");
        return -1;
    }
    printf("Done with binding\n");
    
    printf("Listening for incoming messages...\n\n");
    
    // Receive client's message:
    if (recvfrom(socket_desc, &client_message, sizeof(client_message), 0,
         (struct sockaddr*)&client_addr, &client_struct_length) < 0){
        printf("Couldn't receive\n");
        return -1;
    }
    printf("Received message from IP: %s and port: %i\n",
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    
    printf("Msg from client: struct message{\n\tc=%c\n\td=%d\n\tf=%.2f\n}\n", client_message.c,client_message.d,client_message.f);
    
    close(socket_desc);

}

