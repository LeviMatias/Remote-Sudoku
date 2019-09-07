#include "client_protocol.h"

#define NUMBER_OF_AVAILABLE_COMMANDS 5

const command_struct_t AVAILABLE_COMMANDS[] = {
	{GET, &cmd_parse_single},
	{PUT, &cmd_parse_coordinates},
	{VER, &cmd_parse_single},
	{RES, &cmd_parse_single},
	{EXI, &cmd_exit},
};

int protocol_connect_to_server(protocol_t* self, struct addrinfo* ai){
	return socket_connect(&(self->socket),ai);
}

int protocol_parse_client_input(protocol_t* self, char* input){
	char* saveptr;
	char* cmd_code = strtok_r(input, DELIM_WORDS, &saveptr);
	int s = -1;
	for (int i=0; (cmd_code != NULL) & (i < NUMBER_OF_AVAILABLE_COMMANDS); i++){
		if (strcmp(cmd_code, AVAILABLE_COMMANDS[i].name) == 0){
			s = AVAILABLE_COMMANDS[i].parse_function(\
				self->msg, &(self->msg_size), cmd_code, saveptr);
			if (s == -1){
				break;
			}
		}
	}
	return s;
}

