
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
    struct sockaddr_in server, client1, client2;
    int sockfd, client1_len, client2_len;
    struct Data data;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }


    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    if (bind(sockfd, (const struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for data from client1...\n");
    client1_len = sizeof(client1);
    recvfrom(sockfd, &data, sizeof(data), 0, (struct sockaddr *)&client1, &client1_len);

    data.c += 1;
    data.i += 1;
    data.f += 1.0;

    printf("Sending modified data to client2...\n");
    client2.sin_family = AF_INET;
    client2.sin_addr.s_addr = inet_addr("127.0.0.1");
    client2.sin_port = htons(9999);
    client2_len = sizeof(client2);
    sendto(sockfd, &data, sizeof(data), 0, (const struct sockaddr *)&client2, client2_len);

    printf("Data sent to client2\n");

    close(sockfd);
    return 0;
}
