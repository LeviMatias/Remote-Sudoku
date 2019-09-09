#include "server_command_interpreter.h"

const srv_command_struct_t SERVER_COMMANDS[] = {
	{GET, CMD_LENGTH, &sudoku_print_board},
	{PUT, PUT_LENGTH, &sudoku_place_value},
	{VER, CMD_LENGTH, &sudoku_verify},
	{RES, CMD_LENGTH, &sudoku_reset}
};

void interpreter_init( interpreter_t* self){
	self->current_command = NULL;
}

int interpreter_identify_command(interpreter_t* self, char* inputted_code){
	//search for a match in the available commands
	for (int i=0; (inputted_code != NULL) & (i < NUMBER_SERVER_COMMANDS); i++){
		char cmd_code = toupper(SERVER_COMMANDS[i].name[0]);
		if (inputted_code[0] == cmd_code){
			//return a pointer to the command_struct_t
			self->current_command =(srv_command_struct_t*)&SERVER_COMMANDS[i];
			return SERVER_COMMANDS[i].size;
		}
	}
	return -1;
}

common_message_t* interpreter_execute_command(interpreter_t* self,\
											 sudoku_t* sudoku, char* cmd){
	return self->current_command->sudoku_function(sudoku, cmd);
}

void interpreter_release( interpreter_t* self){
	//nothing to release
}

