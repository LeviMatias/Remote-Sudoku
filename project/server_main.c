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
			int id_res = interpreter_identify_command(&interpreter, &(self->protocol.msg[0]));
			if (id_res > 1){
				r = protocol_receive(&(self->protocol), &(self->protocol.msg[1]), (r - 1));
			}
			if ( id_res > 0 && r > 0){// check again because it may have requested more bytes
				sudoku_message_t* sudoku_rv = interpreter_execute_command(&interpreter, &sudoku, self->protocol.msg);
				uint32_t size = sudoku_rv->size;
				size = htonl(size);
				protocol_send(&(self->protocol), (char*)&size, sizeof(uint32_t));
				protocol_send(&(self->protocol), sudoku_rv->text, sudoku_rv->size);
			}
		}
	}
	return s;
}
