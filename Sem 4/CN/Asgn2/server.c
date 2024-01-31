#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/time.h>
#include <errno.h>

#define MAX_CLIENTS 4

int main(int argc, char const *argv[])
{
    // allow upto max 4 client connections
    int mastersockfd, connfds[MAX_CLIENTS];
    int activeconnections = 0;

    struct sockaddr_in serv_addr, clientIPs[MAX_CLIENTS];
    int addrlen = sizeof serv_addr;
    char inBuffer[MAX_CLIENTS][1024] = {0};
    char outBuffer[MAX_CLIENTS][1024] = {0};

    if ((mastersockfd = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
        perror("Error while creating socket...");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8081);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    int opt = 1;
    setsockopt(mastersockfd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));

    if (bind(mastersockfd, (struct sockaddr *)&serv_addr, addrlen) < 0)
    {
        perror("Bind failed...");
        exit(1);
    }

    if (listen(mastersockfd, 3) < 0)
    {
        perror("Listen failed ...");
        exit(1);
    }

    fd_set readfds;
    int max_fd, readyfds;
    while (1)
    {

        FD_ZERO(&readfds); // used to remove the currently set FD in readfds

        // add mastersockfd
        FD_SET(mastersockfd, &readfds); // set the master (server) socket FD in readfds
        max_fd = mastersockfd;

        for (int i = 0; i < activeconnections; i++)
        {
            if (connfds[i] != 0)
                FD_SET(connfds[i], &readfds);
            if (connfds[i] > max_fd)
                max_fd = connfds[i];
        }

        readyfds = select(max_fd + 1, &readfds, NULL, NULL, NULL);

        if ((readyfds < 0) && (errno != EINTR))
        {
            printf("select error");
        }

        if (FD_ISSET(mastersockfd, &readfds))
        {
            if ((connfds[activeconnections] = accept(mastersockfd, (struct sockaddr *)&clientIPs[activeconnections], (socklen_t *)&addrlen)) < 0)
            {
                perror("accept error...");
                exit(1);
            }

            fprintf(stdout, "New connection from %s\n", inet_ntoa(clientIPs[activeconnections].sin_addr));
            activeconnections++;
        }

        for (int i = 0; i < activeconnections; i++)
        {
            // check if connection is active and it is ready to read
            if (connfds[i] != 0 && FD_ISSET(connfds[i], &readfds))
            {
                // clear buffer
                memset(inBuffer[i], 0, 1024);
                memset(outBuffer[i], 0, 1024);

                // read returns 0 if connection closed normally
                // and -1 if error
                if (read(connfds[i], inBuffer[i], 1024) <= 0)
                {
                    fprintf(stderr, "%s (code: %d)\n", strerror(errno), errno);
                    strncpy(outBuffer[i], inet_ntoa(clientIPs[i].sin_addr), INET_ADDRSTRLEN);
                    fprintf(stderr, "Host %s disconnected\n", outBuffer[i]);
                    close(connfds[i]);
                    connfds[i] = 0;
                    continue;
                }

                // get client ip
                strncpy(outBuffer[i], inet_ntoa(clientIPs[i].sin_addr), INET_ADDRSTRLEN);

                fprintf(stdout, "%s: %s", outBuffer[i], inBuffer[i]);

                strcat(outBuffer[i], " : ");
                strcat(outBuffer[i], inBuffer[i]);

                for (int j = 0; j < activeconnections; j++)
                {
                    if (connfds[j] != 0 && i != j)
                    {
                        write(connfds[j], outBuffer[i], strlen(outBuffer[i]));
                    }
                }
            }
        }
    }

    return 0;
}