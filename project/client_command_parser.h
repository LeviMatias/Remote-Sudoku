#ifndef __CMD_PARSER_H__
#define __CMD_PARSER_H__

#include "common_command.h"
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct{
	char* name;
	int (*parse_function)(char*, size_t*, char*, char*);
}command_struct_t;

//returns exit code
int cmd_exit(char* buffer, size_t* buffer_size,\
					char* cmd_code, char* cmd);

//POS: parses cmd and puts in buffer[0] the first letter (capitalized) of 
//cmd, bufferSize is set to 1;
//returns 0 if successful, -1 otherwise
int cmd_parse_single(char* buffer, size_t* buffer_size,\
					char* cmd_code, char* input);

//POS: parses cmd until EOL, attemps to find a single value and 2 
//coordinates (X:Y) in the [1;9] range
//input param is tokenized
//returns 0 if successful, -1 otherwise
int cmd_parse_coordinates(char* buffer, size_t* buffer_size, 
	char* cmd_code, char* input);

#endif

