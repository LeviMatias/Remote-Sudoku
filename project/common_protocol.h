#include "common_socket.h"
#include "common_command.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
	socket_t socket;
	size_t msg_size;
	char msg[MAX_MESSAGE_LENGTH+1];
	bool ready;
} protocol_t;

int protocol_init(protocol_t* self, struct addrinfo* ai);

//sends data previously parsed with protocol_parse_client_input
//POS: returns 0 if successful, 1 otherwise
int protocol_send(protocol_t* self);

void protocol_release(protocol_t* self);