#include "server_main.h"


int server_network_component_listen_for_client(networkcomp_t* self){
	int s = protocol_init(&(self->protocol), self->result);
	s = protocol_bind_and_listen(&(self->protocol), self->result);
	s = protocol_accept_connection(&(self->protocol), self->result);

	interpreter_t interpreter;
	while (s > 0){
		s = protocol_receive(&(self->protocol), &(self->protocol.msg[0]), 1);
		int res = interpreter_identify_command(&interpreter, &(self->protocol.msg[0]));
		if (res > 1){
			s = protocol_receive(&(self->protocol), &(self->protocol.msg[1]),(*cmd).size - 1);
		}
		if (s > 0){
			int reply_size 1; //get msg size
			char reply[];
			interpreter_execute_command(&interpreter, &(self->protocol.msg[1]));
		}
		//s = server_process_command(cmd, self->protocol.msg);
		//send to client(); //client prints
	}
	return s;
}
