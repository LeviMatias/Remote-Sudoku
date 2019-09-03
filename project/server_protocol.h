#ifndef __S_PROTOCOL_H__
#define __S_PROTOCOL_H__

#include "common_protocol.h"
#include "common_command.h"

int protocol_bind_and_listen(protocol_t* self, struct addrinfo* ai);

//accepts a client
int protocol_accept_connection(protocol_t* self, struct addrinfo* ai);

#endif