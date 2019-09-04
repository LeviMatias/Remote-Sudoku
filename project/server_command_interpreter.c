#include "server_command_interpreter.h"

command_struct_t* identify_command(char* inputted_code){
	//search for a match in the available commands
	for (int i=0; (inputted_code != NULL) & (i < NUMBER_OF_AVAILABLE_SERVER_COMMANDS); i++){
		char cmd_code = toupper(AVAILABLE_SERVER_COMMANDS[i].name[0]);
		if (strcmp(inputted_code, &cmd_code) == 0){
			//return a pointer to the command_struct_t
			return (command_struct_t*)&AVAILABLE_SERVER_COMMANDS[i];
		}
	}
	return NULL;
}

int execute_command(command_struct_t* cmd, char* msg){
	return 1;
}