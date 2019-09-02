#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include "common_command.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

extern const command_struct_t AVAILABLE_COMMANDS[];

typedef struct {
	//socket
	size_t msg_size;
	char msg[MAX_MESSAGE_LENGTH+1];
	bool ready;
} protocol_t;

//receives a string inputted by the user and parses it so it can be sent
//POS: returns 0 if command was valid
int protocol_parse_client_input(protocol_t* self, char* input);

//int protocol_send();

#endif