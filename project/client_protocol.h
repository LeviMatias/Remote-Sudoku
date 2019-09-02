#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "common_socket.h"
#include "client_command_parser.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

extern const command_struct_t AVAILABLE_COMMANDS[];

typedef struct {
	socket_t socket;
	size_t msg_size;
	char msg[MAX_MESSAGE_LENGTH+1];
	bool ready;
} protocol_t;

int protocol_init(protocol_t* self, struct addrinfo* ai);

//receives a string inputted by the user and parses it so it can be sent
//POS: returns 0 if command was valid, -1 if not, 1 if exit
int protocol_parse_client_input(protocol_t* self, char* input);

//sends data previously parsed with protocol_parse_client_input
//POS: returns 0 if successful, 1 otherwise
int protocol_send(protocol_t* self);

void protocol_release(protocol_t* self);

#endif