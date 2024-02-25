#include <string.h>

typedef char *ddreq_packet;

typedef char *ddres_packet;
char ETR[] = "\x03";  // end of transmission
char NAME[] = "\x01"; // name request header
char NUM[] = "\x09";  // number request header

// used by server to identify packet type.
int getReqType(ddreq_packet packet);
int getReqType(ddreq_packet packet)
{

    // returns 0 for num request, 1 for name request

    if (packet[0] == NUM[0])
        return 0;
    else
        return 1;
}

// server uses it to parse the data (request) sent by the client
int getReqData(ddreq_packet packet, char *buff, int size);
int getReqData(ddreq_packet packet, char *buff, int size)
{

    // gets request data and puts it into buff
    // read packet data till ETR value found in packet, and store that in buff.
    // starting from index 1, so only the message is obtained (name or num, not the type)

    int ct = 0;
    while (packet[1 + ct] != ETR[0] && ct < size - 2)
    {
        buff[ct] = packet[ct + 1];
        ct++;
    }
    return ct;
}

// client uses it to receive the data that the server sends
int getResData(ddreq_packet packet, char *buff, int size);
int getResData(ddreq_packet packet, char *buff, int size)
{

    // gets response data and stores it in buff
    // returns bytes received

    int ct = 0;
    
    while (packet[ct] != ETR[0] && ct < size - 2)
    {
        buff[ct] = packet[ct];
        ct++;
    }
    return ct;
}

// protocol function to send a req packet from client to server
// basically contains all the info that the server needs to know to perform the search (type, message, EOL)

int ddreq_send(int sockfd, char *message, int size, int type);
int ddreq_send(int sockfd, char *message, int size, int type)
{

    // Sends a dd packet and returns bytes sent

    ddreq_packet pacAddr = (ddreq_packet)malloc(size * sizeof(char) + 4);

    if (type == 0)
    {
        // indicates number
        // header value is 9 in decimal
        strcat(pacAddr, NUM);
    }
    else
    {
        // indicates name
        // header value is 1 in decimal
        strcat(pacAddr, NAME);
    }

    strcat(pacAddr, message);
    strcat(pacAddr, ETR);
    
    // basically the pacAddr now looks like: "type + message + end"
	// this is finally what's being sent to the server.
    return send(sockfd, pacAddr, sizeof(size * sizeof(char) + 4), 0);
}

void packet_check(char *message, int size, int type)
{

    // checks packet data

    ddreq_packet pacAddr = (ddreq_packet)malloc(size * sizeof(char) + 4);
    // pacAddr="";

    if (type == 0)
    {
        // indicates number
        strcat(pacAddr, NUM);
    }
    else
    {
        // indicates name
        strcat(pacAddr, NAME);
    }
    // strcat(pacAddr," ");
    strcat(pacAddr, message);
    strcat(pacAddr, ETR);
    char buff[50];
    getReqData(pacAddr, buff, 50);
    printf("Type is %d and data is %s", getReqType(pacAddr), buff);
}

// protocol function to send a response packet
int ddres_send(int sockfd, char *message, int size);
int ddres_send(int sockfd, char *message, int size)
{

    // sends a response packet and returns number of bytes sent

    ddres_packet pacAddr = (ddreq_packet)malloc(size * sizeof(char) + 2);

    strcat(pacAddr, message);
    strcat(pacAddr, ETR);
	
	// used for sending to the client
    return send(sockfd, pacAddr, sizeof(size * sizeof(char) + 2), 0);
}


