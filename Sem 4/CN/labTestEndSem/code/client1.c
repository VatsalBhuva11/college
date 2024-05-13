
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

struct Data {
    char c;
    int i;
    float f;
};

int main() {
    struct sockaddr_in server;
    int sockfd;
    struct Data data;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8888);

    data.c = 'A';
    data.i = 42;
    data.f = 3.14;

    sendto(sockfd, &data, sizeof(data), 0, (const struct sockaddr *)&server, sizeof(server));

    printf("Data sent to server:\n");
    printf("Char: %c\n", data.c);
    printf("Int: %d\n", data.i);
    printf("Float: %f\n", data.f);

    close(sockfd);
    return 0;
}
