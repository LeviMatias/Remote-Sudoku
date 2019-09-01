#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

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

extern const char commands[][7];

typedef struct {
	//socket
	size_t msg_size;
	char msg[MAX_MESSAGE_LENGTH+1];
	bool ready;
} protocol_t;

//receives a string inputted by the user and parses it so it can be sent
//POS: returns 0 if command was valid
int protocol_parse_client_input(protocol_t* self, char* input);

//int protocol_send();

#endif