#include "common_protocol.h"

int protocol_init(protocol_t* self, struct addrinfo* ai){
	memset(self->msg.text, '\0', MAX_MESSAGE_LENGTH+1);
	return socket_init(&(self->socket),ai);
}

int protocol_send(protocol_t* self, char* msg, size_t size){
	return socket_send(&(self->socket), msg, size);
}

int protocol_receive(protocol_t* self, char* buffer, size_t size){
	int bytes_recv = socket_receive(&(self->socket), buffer, size);
	//add null character to self->msg.text end so its ready to use
	memset(&(self->msg.text[bytes_recv + 1]), '\0', 1);
	return bytes_recv;
}

void protocol_release(protocol_t* self){
	socket_release(&(self->socket));
}

