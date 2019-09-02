#include "common_command.h"

typedef struct{
	char* name;
	int length;
	int (*parse_function)(char*, size_t*, char*);//buffer, buffer size, cmd msg
}command_struct_t;

//returns exit code
int cmd_exit(char* buffer, size_t* buffer_size, char* cmd);

//POS: parses cmd and puts in buffer[0] the first letter (capitalized) of cmd, bufferSize is set to 1;
//returns 0 if successful, -1 otherwise
int cmd_parse_single(char* buffer, size_t* buffer_size, char* cmd);

//POS: parses cmd until EOL, attemps to find a single value and 2 coordinates (X:Y) in the [1;9] range
//returns 0 if successful, -1 otherwise
int cmd_parse_coordinates(char* buffer, size_t* buffer_size, char* cmd);