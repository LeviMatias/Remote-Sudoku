#define _POSIX_C_SOURCE 200112L
#include "common_socket.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

void socket_init(socket_t* self, struct addrinfo* ai){
	self->fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
}

int socket_connect(socket_t* self, const char* host, const char* service){
	return 0;
}

void socket_release(socket_t* self){
	close(self->fd);
}