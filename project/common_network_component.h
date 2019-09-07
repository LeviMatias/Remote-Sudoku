#ifndef __NETWORK_COMP_H__
#define __NETWORK_COMP_H__

#include "common_protocol.h"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <netdb.h>

typedef struct {
	struct addrinfo hints;
	struct addrinfo *result;
	protocol_t protocol;
} networkcomp_t;

//prepares the component for communication to the specified host and service
//POS returns 0 if successful, -1 otherwise
int network_component_start(networkcomp_t* self, const char* hostname,\
							 const char* servicename, bool is_passive);

//finalize the component
void network_component_shutdown(networkcomp_t* self);

#endif
