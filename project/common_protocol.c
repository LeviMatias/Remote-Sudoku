#include "common_protocol.h"

int protocol_init(protocol_t* self, struct addrinfo* ai){
	memset(&(self->msg), '0', MAX_MESSAGE_LENGTH+1);
	return socket_init(&(self->socket),ai);
}

int protocol_send(protocol_t* self, char* msg, size_t size){
	if (self->ready){
		return socket_send(&(self->socket), msg, size);
	} else {
		printf("There is no valid command set\n");
		return -1;
	}
}

int protocol_receive(protocol_t* self, char* buffer, size_t size){
	return socket_receive(&(self->socket), buffer, size);
}

void protocol_release(protocol_t* self){
	socket_release(&(self->socket));
}