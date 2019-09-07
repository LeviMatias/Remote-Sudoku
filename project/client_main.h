#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "common_network_component.h"
#include "client_protocol.h"

//attemps to connect
//POS: returns exit value, 0 if everything went smoothly -1 otherwise
int client_network_component_connect(networkcomp_t* self);

//starts listening for local input which is sent to the server
//POS: returns exit value, 0 if everything went smoothly -1 otherwise
int client_network_component_play(networkcomp_t* self);


#endif
