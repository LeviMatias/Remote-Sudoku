#include "server_main.h"


int server_network_component_listen_for_client(networkcomp_t* self){
	int s = protocol_init(&(self->protocol), self->result);
	s = protocol_bind_and_listen(&(self->protocol), self->result);
	s = protocol_accept_connection(&(self->protocol), self->result);
	interpreter_t interpreter;
	sudoku_t sudoku;
	s = sudoku_init(&sudoku);

	int r = 1;
	while (r > 0){
		r = protocol_receive(&(self->protocol), &(self->protocol.msg[0]), 1);// recv cmd key
		if (r > 0){
			r = interpreter_identify_command(&interpreter, &(self->protocol.msg[0]));
			if (r > 1){
				r = protocol_receive(&(self->protocol), &(self->protocol.msg[1]), (r - 1));
			}
			if (r > 0){// check again because it may have requested more bytes
				interpreter_execute_command(&interpreter, &sudoku, self->protocol.msg);
			}
		}
		//s = server_process_command(cmd, self->protocol.msg);
		//send to client(); //client prints
	}
	return s;
}
