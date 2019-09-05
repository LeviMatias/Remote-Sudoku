#ifndef __S_CMD_INTERPRETER_H__
#define __S_CMD_INTERPRETER_H__

#include "common_command.h"
#include "server_sudoku.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct{
	char* name;
	size_t size;
	sudoku_message_t* (*sudoku_function)(sudoku_t*, char*);//buffer, buffer size, cmd msg
}server_command_struct_t;

typedef struct{
	server_command_struct_t* current_command;
}interpreter_t;

#define NUMBER_OF_AVAILABLE_SERVER_COMMANDS 4

extern const server_command_struct_t AVAILABLE_SERVER_COMMANDS[];

// attempts to identify command, 
//POS if successful returns number of bytes needed to be received from client to execute
// and sets the command to self.current_command, else returns -1
int interpreter_identify_command(interpreter_t* self, char* cmd_code);

//PRE it should have a previously identified command set as current_command
//POS executes function over sudoku
sudoku_message_t* interpreter_execute_command(interpreter_t* self, sudoku_t* sudoku, char* cmd);

#endif