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
	protocol_t* prtcl_ptr = &(self->protocol);
	char* msg = prtcl_ptr->msg;
	while (s != EXIT_CODE && r > 0 && fgets(word, sizeof(word), stdin)){
		s = protocol_parse_client_input(prtcl_ptr, word);
		if (s == 0){
			r = protocol_send(prtcl_ptr, msg, prtcl_ptr->msg_size);

			uint32_t bytes_to_rcv;
			r = protocol_receive(prtcl_ptr,\
			 (char*)&bytes_to_rcv, sizeof(uint32_t));//get server reply

			if (r > 0){
				bytes_to_rcv = ntohl(bytes_to_rcv);
				r = protocol_receive(prtcl_ptr, msg, bytes_to_rcv);
				printf("%s", msg);
			}
			if (r < 0){
				fprintf(stderr,"Connection forcefully terminated \n");
			}
		}
	}
	if (s == EXIT_CODE){
		s = 0; // execution was successful
	}
	return s;
}

