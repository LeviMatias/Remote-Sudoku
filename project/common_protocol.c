#include "common_protocol.h"

#define NUMBER_OF_COMMANDS 5
#define PUT_LENGTH 4

const command_struct_t AVAILABLE_COMMANDS[] = {
	{GET, 1, &parse_single},
	{PUT, 4, &parse_coordinates},
	{VER, 1, &parse_single},
	{RES, 1, &parse_single},
	{EXI, 1, &parse_single},
};

int protocol_parse_client_input(protocol_t* self, char* input){
	char* cmd = strtok(input, DELIM_WORDS);
	int s = 1;
	self->ready = false;
	for (int i=0; i<NUMBER_OF_COMMANDS; i++){
		if (strcmp(cmd, AVAILABLE_COMMANDS[i].name) == 0){
			s = AVAILABLE_COMMANDS[i].parse_function(self->msg, &(self->msg_size), cmd);
			if (s == 0){
				self->ready = true;
			}
		}
	}
	if (s == 1){
		printf("Invalid command\n");
	}
	return s;
}