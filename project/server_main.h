#ifndef __SERVER_H__
#define __SERVER_H__

#include "common_network_component.h"
#include "server_protocol.h"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

int server_network_component_listen_for_client(networkcomp_t* self);

#endif