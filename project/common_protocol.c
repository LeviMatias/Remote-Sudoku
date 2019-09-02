#include "common_protocol.h"

int protocol_init(protocol_t* self, struct addrinfo* ai){
	return socket_init(&(self->socket),ai);
}

int protocol_send(protocol_t* self){
	if (self->ready){
		return socket_send(&(self->socket), (self->msg), (self->msg_size));
	} else {
		printf("There is no valid command set\n");
		return -1;
	}
}

void protocol_release(protocol_t* self){
	socket_release(&(self->socket));
}