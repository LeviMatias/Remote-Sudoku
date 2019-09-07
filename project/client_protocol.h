#ifndef __CLIENT_PROTOCOL_H__
#define __CLIENT_PROTOCOL_H__

#include "common_protocol.h"
#include "common_command.h"
#include "client_command_parser.h"

#include <string.h>
#include <ctype.h>
#include <stdbool.h>

extern const command_struct_t AVAILABLE_COMMANDS[];

//attemps to connect to the server
//PRE protocol must be initialized
//POS 0 if successful, -1 otherwise
int protocol_connect_to_server(protocol_t* self, struct addrinfo* ai);

//receives a string inputted by the user and parses it so it can be sent
//POS: returns 0 if command was valid, -1 if not, 1 if exit
//input param is tokenized
int protocol_parse_client_input(protocol_t* self, char* input);

#endif
