#ifndef __SERVER_H__
#define __SERVER_H__

#include "common_network_component.h"
#include "server_protocol.h"
#include "server_command_interpreter.h"
#include "server_sudoku.h"

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

//listens and accepts the connection of one client
//POS returns 0 if successful, -1 if not
int server_network_component_listen_for_client(networkcomp_t* self);

//begins accepting input for the game the game
//PRE server_network_component_listen_for_client should be ran and successful
//POS returns exit code 0 if successful, -1 if error ocurred
int server_network_component_play(networkcomp_t* self);

#endif

