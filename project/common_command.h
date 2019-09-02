#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_MESSAGE_LENGTH 4
#define UPPER_BOUND "9"
#define LOWER_BOUND "1"

#define DELIM_WORDS " ,\n"
#define GET "get"
#define PUT "put"
#define VER "verify"
#define RES "reset"
#define EXI "exit"
#define PUT_LENGTH 4

typedef struct{
	char* name;
	int length;
	int (*parse_function)(char*, size_t*, char*);//buffer, buffer size, cmd msg
}command_struct_t;

//POS: parses cmd and puts in buffer[0] the first letter (capitalized) of cmd, bufferSize is set to 1;
//returns 0 if successful, 1 otherwise
int parse_single(char* buffer, size_t* buffer_size, char* cmd);

//POS: parses cmd until EOL, attemps to find a single value and 2 coordinates (X:Y) in the [1;9] range
//returns 0 if successful, 1 otherwise
int parse_coordinates(char* buffer, size_t* buffer_size, char* cmd);

#endif