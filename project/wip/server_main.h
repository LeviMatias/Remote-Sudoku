#ifndef __SERVER_H__
#define __SERVER_H__

#include "common_socket.h"

typedef struct{
	socket_t socket;
	struct addrinfo hints;
	struct addrinfo *result;
} server_t;

//starts a new instance of the server and begins to listen for connections
void server_start(server_t* self, const char* hostname, const char* servicename);

int server_listen(server_t*);

//finalize the server
void server_shutdown(server_t* self);

#endif