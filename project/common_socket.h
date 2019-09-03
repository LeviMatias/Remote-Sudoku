#ifndef __SOCKET_H__
#define __SOCKET_H__
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define NOT_CONNECTED -1

typedef struct {
	//file descriptor
	int fd;
	// file descriptor of the socket's channel ( == fd if client)
	int connected;
} socket_t;

//initializes a to the addrinfo specified
//POS: returns socket filedescriptor if succeeded -1 if not
int socket_init(socket_t* self, struct addrinfo* ai);

//attemps to connect to the addrinfo specified
//POS: returns 0 if succeeded, otherwise returns -1 and closes the socket
int socket_connect(socket_t* self, struct addrinfo* ai);

//POS: returns fd if successful, -1 if error
int socket_bind_and_listen(socket_t* self, struct addrinfo* ai);

//POS returns connection fd and sets it to self->connected, -1 if not successful
int socket_accept(socket_t* self, struct addrinfo* ai);

int socket_send(socket_t* self, const char* buffer, size_t size);

//POS returns number of bytes received, 0 if connection is closed, -1 if error
int socket_receive(socket_t* self, char* buffer, size_t size);

bool socket_is_connected(socket_t* self);

void socket_release(socket_t* self);

#endif