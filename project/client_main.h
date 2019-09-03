#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "client_protocol.h"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

typedef struct {
	struct addrinfo hints;
	struct addrinfo *result;
	protocol_t protocol;
} client_t;

//prepares the client to connect to the specified host and service
void client_start(client_t* self, const char* hostname, const char* servicename);

//attemps to connect
//POS: returns exit value, 0 if everything went smoothly -1 otherwise
int client_connect(client_t* self);

//starts listening for local input which is sent to the server
//POS: returns exit value, 0 if everything went smoothly -1 otherwise
int client_play(client_t* self);

//finalize the client
void client_shutdown(client_t* self);

#endif