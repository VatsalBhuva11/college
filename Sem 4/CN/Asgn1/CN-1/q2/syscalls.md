socket():
Creates an communication pipe and returns a file descriptor that refers to that endpoint.
Parameters: domain, type, protocol

bind():
Binds a name/local address to socket.
Parameters: int sockf, sockaddr \*addr, socklen_t addrlen

connect():
Initiates a connection on a socket.
Parameters: int sockfd, const struct sockaddr *addr, socklen_t addrlen

listen():
Sets a socket to passive mode, ready to accept incoming connections.
Parameters: int sockfd, int backlog

accept():
Accepts a connection on a socket.
Parameters: int sockfd, struct sockaddr *addr, socklen_t *addrlen

send():
Sends data on a connected socket.
Parameters: int sockfd, const void *buf, size_t len, int flags

recv():
Receives data on a connected socket.
Parameters: int sockfd, void *buf, size_t len, int flags

sendto():
Sends data to a specific destination.
Parameters: int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen

recvfrom():
Receives data from a specific source.
Parameters: int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen

close():
Closes a socket.
Parameters: int sockfd

shutdown():
Disables sends or receives on a socket.
Parameters: int sockfd, int how

fork():
Creates a new process by duplicating the calling process.
Parameters: None
