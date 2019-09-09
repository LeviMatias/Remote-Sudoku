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
	common_message_t* (*sudoku_function)(sudoku_t*, char*);
}srv_command_struct_t;

typedef struct{
	srv_command_struct_t* current_command;
}interpreter_t;

#define NUMBER_SERVER_COMMANDS 4

extern const srv_command_struct_t SERVER_COMMANDS[];

//class constructor
void interpreter_init( interpreter_t* self);

// attempts to identify command, 
//POS if successful returns number of bytes needed to be received from client
//to execute and sets the command to self.current_command, else returns -1
int interpreter_identify_command(interpreter_t* self, char* cmd_code);

//PRE it should have a previously identified command set as current_command
//POS executes function over sudoku
common_message_t* interpreter_execute_command(interpreter_t* self,\
										sudoku_t* sudoku, char* cmd);

//class destructor
void interpreter_release( interpreter_t* self);

#endif

