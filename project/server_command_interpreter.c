#include "server_command_interpreter.h"

const server_command_struct_t AVAILABLE_SERVER_COMMANDS[] = {
	{GET, CMD_LENGTH},// &sudoku_print},
	{PUT, PUT_LENGTH},// &sudoku_place},
	{VER, CMD_LENGTH},// &sudoku_verify},
	{RES, CMD_LENGTH},// &sudoku_reset}
};

int interpreter_identify_command(interpreter_t* self, char* inputted_code){
	//search for a match in the available commands
	for (int i=0; (inputted_code != NULL) & (i < NUMBER_OF_AVAILABLE_SERVER_COMMANDS); i++){
		char cmd_code = toupper(AVAILABLE_SERVER_COMMANDS[i].name[0]);
		if (strcmp(inputted_code, &cmd_code) == 0){
			//return a pointer to the command_struct_t
			self->current_command =(server_command_struct_t*)&AVAILABLE_SERVER_COMMANDS[i];
			return AVAILABLE_SERVER_COMMANDS[i].size;
		}
	}
	return -1;
}

int interpreter_execute_command(interpreter_t* self){
	return 1;
}