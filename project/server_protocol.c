#include "server_protocol.h"

int protocol_bind_and_listen(protocol_t* self, struct addrinfo* ai){
	return socket_bind_and_listen(&(self->socket), ai);
}

//accepts a client
int protocol_accept_connection(protocol_t* self, struct addrinfo* ai){
	return socket_accept(&(self->socket), ai);
}

