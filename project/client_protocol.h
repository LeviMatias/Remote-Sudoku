#ifndef __CLIENT_PROTOCOL_H__
#define __CLIENT_PROTOCOL_H__

#include "common_protocol.h"
#include "client_command_parser.h"

#include <string.h>
#include <ctype.h>
#include <stdbool.h>

extern const command_struct_t AVAILABLE_COMMANDS[];

extern int protocol_init(protocol_t* self, struct addrinfo* ai);
extern int protocol_send(protocol_t* self);
extern int protocol_receive(protocol_t* self);
extern void protocol_release(protocol_t* self);

//receives a string inputted by the user and parses it so it can be sent
//POS: returns 0 if command was valid, -1 if not, 1 if exit
int protocol_parse_client_input(protocol_t* self, char* input);

#endif