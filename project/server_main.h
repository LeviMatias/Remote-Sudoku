#ifndef __SERVER_H__
#define __SERVER_H__

#include "server_protocol.h"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

typedef struct {
	struct addrinfo hints;
	struct addrinfo *result;
	protocol_t protocol;
} server_t;

void server_start(server_t* self, const char* hostname, const char* servicename);

int server_listen_for_client(server_t* self);

void server_shutdown(server_t* self);


#endif