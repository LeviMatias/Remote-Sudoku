#include "server_command_interpreter.h"

const server_command_struct_t AVAILABLE_SERVER_COMMANDS[] = {
	{GET, CMD_LENGTH, &sudoku_print},
	{PUT, PUT_LENGTH, &sudoku_place_value},
	{VER, CMD_LENGTH, &sudoku_verify},
	{RES, CMD_LENGTH, &sudoku_reset}
};

int interpreter_identify_command(interpreter_t* self, char* inputted_code){
	//search for a match in the available commands
	for (int i=0; (inputted_code != NULL) & (i < NUMBER_OF_AVAILABLE_SERVER_COMMANDS); i++){
		char cmd_code = toupper(AVAILABLE_SERVER_COMMANDS[i].name[0]);
		if (inputted_code[0] == cmd_code){
			//return a pointer to the command_struct_t
			self->current_command =(server_command_struct_t*)&AVAILABLE_SERVER_COMMANDS[i];
			return AVAILABLE_SERVER_COMMANDS[i].size;
		}
	}
	return -1;
}

sudoku_message_t* interpreter_execute_command(interpreter_t* self, sudoku_t* sudoku, char* cmd){
	return self->current_command->sudoku_function(sudoku, cmd);
}