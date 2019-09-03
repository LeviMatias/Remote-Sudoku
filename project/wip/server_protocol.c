#include "server_protocol.h"

int protocol_bind_and_listen(protocol_t* self, struct addrinfo* ai){
	return self->socket_bind_and_listen(&(self->socket), ai)
}

//accepts a client
int protocol_accept_connection(protocol_t* self, struct addrinfo* ai){
	return self->socket_accept(&(self->socket), ai)
}