#include "server_main.h"


int server_network_component_listen_for_client(networkcomp_t* self){
	int s = protocol_init(&(self->protocol), self->result);
	s = protocol_bind_and_listen(&(self->protocol), self->result);
	s = protocol_accept_connection(&(self->protocol), self->result);

	while (s > 0){
		s = protocol_receive(&(self->protocol), &(self->protocol.msg[0]), 1);
		printf("success\n");
		//s = protocol_process_command();
	}
	return s;
}
