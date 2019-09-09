#include "server_main.h"


int server_network_component_listen_for_client(networkcomp_t* self){
	int s = protocol_init(&(self->protocol), self->result);
	if (s != -1){
		s = protocol_bind_and_listen(&(self->protocol), self->result);
	}
	if (s != -1){
		s = protocol_accept_connection(&(self->protocol), self->result);
	}
	return s;
}

int server_network_component_play(networkcomp_t* self){
	interpreter_t interpreter;
	sudoku_t sudoku;
	int s = sudoku_init(&sudoku, &(self->protocol.msg));

	int r = 1;
	while (r > 0 && s != -1){
		//recv cmd key
		r = protocol_receive(&(self->protocol), self->protocol.msg.text, 1);
		if (r > 0){
			int bytes_needed = interpreter_identify_command(&interpreter,\
												 self->protocol.msg.text);
			if (bytes_needed > 1){
				r = protocol_receive(&(self->protocol),\
							 self->protocol.msg.text, (bytes_needed - 1));
			}
			if (bytes_needed > 0 && r > 0){
				common_message_t* sudoku_rv = interpreter_execute_command(\
									&interpreter, &sudoku, self->protocol.msg.text);
				uint32_t size = sudoku_rv->size;
				size = htonl(size);
				r = protocol_send(&(self->protocol), (char*)&size,\
							 sizeof(uint32_t));
				r = protocol_send(&(self->protocol), sudoku_rv->text,\
								sudoku_rv->size);
			}
		}
	}
	return r;
}
