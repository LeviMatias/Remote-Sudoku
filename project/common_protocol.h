#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "common_socket.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_MESSAGE_LENGTH 4 //in bytes

typedef struct {
	socket_t socket;
	size_t msg_size;
	char msg[MAX_MESSAGE_LENGTH+1];//used for default cmd communication
} protocol_t;

//initializes the socket and prepares the protocol to operate
//returns 0 if successful init
int protocol_init(protocol_t* self, struct addrinfo* ai);

//sends msg through the channel
//POS: returns bytes sent if successful, -1 otherwise
int protocol_send(protocol_t* self, char* msg, size_t size);

//listens for #size elements that places in buffer
//POS returns -1 if not successful, otherwise returns number of bytes received
int protocol_receive(protocol_t* self, char* buffer, size_t size);

void protocol_release(protocol_t* self);

#endif