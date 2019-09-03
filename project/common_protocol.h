#include "common_socket.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_MESSAGE_LENGTH 4 //in bytes

typedef struct {
	socket_t socket;
	size_t msg_size;
	char msg[MAX_MESSAGE_LENGTH+1];
	bool ready;
} protocol_t;

//initializes the socket and prepares the protocol to operate
//returns 0 if successful init
int protocol_init(protocol_t* self, struct addrinfo* ai);

//sends data previously parsed with protocol_parse_client_input
//POS: returns bytes sent if successful, -1 otherwise
int protocol_send(protocol_t* self);

//listens for size elemnts that places in buffer
//POS returns -1 if not successful, otherwise returns number of bytes received
int protocol_receive(protocol_t* self, char* buffer, size_t size);

void protocol_release(protocol_t* self);