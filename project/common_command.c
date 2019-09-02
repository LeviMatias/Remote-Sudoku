#include "common_command.h"

int parse_single(char* buffer, size_t* buffer_size, char* cmd){
	buffer[0] = toupper(*cmd);
	*buffer_size = 1;
	return 0;
}

int parse_coordinates(char *buffer, size_t *buffer_size, char *cmd){
	int s = parse_single(buffer, buffer_size, cmd);

	cmd = strtok(NULL, DELIM_WORDS);
	while (cmd != NULL){ //begin extracting parameters from the message
		if (isdigit(*cmd)){
			if (*cmd > *UPPER_BOUND || *cmd < *LOWER_BOUND){
				printf("Index error. Supported range: [1,9] inputted: %s\n",cmd);
				return 1;
			}
			buffer[*buffer_size] = *cmd;
			(*buffer_size)++;
		}
		cmd = strtok(NULL, DELIM_WORDS);
	}
	if (*buffer_size != PUT_LENGTH){
		return 1;
	}
	int aux = buffer[1];
	buffer[1] = buffer[2];
	buffer[2] = buffer[3]; 
	buffer[3] = aux;
	return s;
}