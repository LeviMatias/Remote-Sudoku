#include "common_protocol.h"

const char commands[][7] = {GET,PUT,VER,RES,EXI};

int const protocol_add_message(protocol_t* self, char* cmd){
	self->msg[0] = toupper(*cmd);
	self->msg_size = 1;

	//PUT is the only command that requires additional parameters
	if (strcmp(cmd,PUT) == 0){
		cmd = strtok(NULL, DELIM_WORDS);
		while (cmd != NULL){ //begin extracting parameters from the message
			printf("is command %s\n",cmd);
			if (isdigit(*cmd)){
				if (*cmd > *UPPER_BOUND || *cmd < *LOWER_BOUND){
					printf("Index error. Supported range: [1,9] inputted: %s\n",cmd);
					return 1;
				}
				self->msg[self->msg_size] = *cmd;
				self->msg_size++;
			}
			cmd = strtok(NULL, DELIM_WORDS);
		}
		//add error for when msg doesnt have all parts
		int aux = self->msg[1];
		self->msg[1] = self->msg[2];
		self->msg[2] = self->msg[3]; 
		self->msg[3] = aux;
	}
	self->ready = true;
	return 0;
}

int protocol_parse_client_input(protocol_t* self, char* input){
	char* cmd = strtok(input, DELIM_WORDS);
	int s = 1;
	self->ready = false;
	for (int i=0; i<(sizeof(commands)/sizeof(commands[0])); i++){
		if (strcmp(cmd, commands[i]) == 0){
			s = protocol_add_message(self, cmd);
		}
	}
	if (s == 1){
		printf("Invalid command\n");
	}
	return s;
}