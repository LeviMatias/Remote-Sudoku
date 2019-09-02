#ifndef __SOCKET_H__
#define __SOCKET_H__
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdbool.h>

#define CONNECTED 0
#define NOT_CONNECTED -1

typedef struct {
	int fd; //file descriptor
	int connected;
	//type, server or client
	char* host;
	char* service; //port
} socket_t;

//initializes and connects a socket to the addrinfo specified
//POS: returns 0 if succeeded -1 if not
int socket_init(socket_t* self, struct addrinfo* ai);

int socket_bind_and_listen(socket_t* self, struct addrinfo* ai);

int socket_send(socket_t* self, const char* buffer, size_t size);

int socket_receive(socket_t* self, const char* buffer, size_t size);

bool socket_is_connected(socket_t* self);

void socket_release(socket_t* self);

#endif