#ifndef __S_CMD_INTERPRETER_H__
#define __S_CMD_INTERPRETER_H__

#include "common_command.h"
//include sudoku
#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct{
	char* name;
	int size;
	int (*sudoku_function)(char*, size_t*, char*);//buffer, buffer size, cmd msg
}server_command_struct_t;

typedef struct{
	server_command_struct_t* current_command;
}interpreter_t;

#define NUMBER_OF_AVAILABLE_SERVER_COMMANDS 4

const server_command_struct_t AVAILABLE_SERVER_COMMANDS[] = {
	{GET, CMD_LENGTH},// &sudoku_print},
	{PUT, PUT_LENGTH},// &sudoku_place},
	{VER, CMD_LENGTH},// &sudoku_verify},
	{RES, CMD_LENGTH},// &sudoku_reset}
};

// attempts to identify command, if successful returns a pointer to the cmd, else returns a NULL pointer
int interpreter_identify_command(interpreter_t self, char* cmd_code);

int interpreter_execute_command(interpreter_t* self, char* msg); //sudoku_t* sudoku

#endif