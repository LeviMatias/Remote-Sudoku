#include "client_command_parser.h"
const char PUT_STRUCTURE[][3] = {"put","X","in","X","X"};

int cmd_exit(char* buffer, size_t* buffer_size, char* cmd){
	return EXIT_CODE;
}

int cmd_parse_single(char* buffer, size_t* buffer_size, char* cmd){
	buffer[0] = toupper(*cmd);
	*buffer_size = 1;
	return 0;
}

int cmd_parse_coordinates(char *buffer, size_t *buffer_size, char *cmd){
	int s = cmd_parse_single(buffer, buffer_size, cmd);
	int i = 1;

	cmd = strtok(NULL, DELIM_WORDS);
	while (cmd != NULL && (strcmp(PUT_STRUCTURE[i],"X") == 0  || strcmp(cmd,PUT_STRUCTURE[i]) == 0 )){ 
	//begin extracting parameters from the message
		if (isdigit(*cmd) != 0){
			if (*cmd > *UPPER_BOUND || *cmd < *LOWER_BOUND){
				printf("Index error. Supported range: [1,9] inputted: %s\n",cmd);
				return -1;
			}
			buffer[*buffer_size] = *cmd;
			(*buffer_size)++;
		}
		cmd = strtok(NULL, DELIM_WORDS);
		i++;
	}
	if (*buffer_size != PUT_LENGTH){
		return -1;
	}
	int aux = buffer[1];
	buffer[ROW_IS_IN] = buffer[2];
	buffer[COLUMN_IS_IN] = buffer[3]; 
	buffer[VALUE_IS_IN] = aux;
	return s;
}