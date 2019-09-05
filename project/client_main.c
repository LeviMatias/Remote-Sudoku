#include "client_main.h"

int client_network_component_connect(networkcomp_t* self){
	int s = -1;
	struct addrinfo* ptr;
	for (ptr = self->result; ptr != NULL && s == -1; ptr = ptr->ai_next){
		s = protocol_init(&(self->protocol), ptr);
		if (s != -1){
			s = protocol_connect_to_server(&(self->protocol), ptr);
		}
	}
	if (s == -1){
		printf("Could not connect \n");
	}
	return s;
}

int client_network_component_play(networkcomp_t* self){
	int s = -1;
	int r = 1;
	char word[12+1];
	while ( s != EXIT_CODE && r > 0 && fgets(word, sizeof(word), stdin)){
		s = protocol_parse_client_input(&(self->protocol), word);
		if (s == 0){
			protocol_send(&(self->protocol), self->protocol.msg, self->protocol.msg_size);
			uint32_t msg_length;
			r = protocol_receive(&(self->protocol), (char*)&msg_length, sizeof(uint32_t));
			if (r > 0){
				msg_length = ntohl(msg_length);
				char msg[msg_length];
				r = protocol_receive(&(self->protocol), &(msg[0]), msg_length);
				printf("print msg: %s\n", msg);
			}
			if (r  < 0 ){
				printf("Connection forcefully terminated \n");
			}
		}
	}
	if (s == EXIT_CODE){
		s = 0; // execution was successful
	}
	return s;
}