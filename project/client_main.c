#include "client_main.h"

void client_start(client_t* self, const char* hostname, const char* servicename){

	memset(&(self->hints), 0, sizeof(self->hints));
	self->hints.ai_family = AF_INET;       /* IPv4 */
	self->hints.ai_socktype = SOCK_STREAM; /* TCP */
	self->hints.ai_flags = 0;

	int s = getaddrinfo(hostname, servicename, &(self->hints), &(self->result));
	if (s != 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      return;
   }
}

int client_connect(client_t* self){
	int s = -1;
	struct addrinfo* ptr;
	for (ptr = self->result; ptr != NULL && s == -1; ptr = ptr->ai_next){
		s = protocol_init(&(self->protocol), ptr);
		if (s != -1){
			s = protocol_connect_to_server(&(self->protocol), ptr);
		}
	}
	if (s == -1){
		printf("Could not connect: \n");
	}
	return s;
}

int client_play(client_t* self){
	int s = -1;
	char word[12+1];
	while (fgets(word, sizeof(word), stdin) && s != EXIT_CODE){
		int s = protocol_parse_client_input(&(self->protocol), word);
		if (s == 0){
			protocol_send(&(self->protocol));
			uint32_t msg_length;
			int r = protocol_receive(&(self->protocol), (char*)&msg_length, sizeof(uint32_t));
			if (r >= 0){
				msg_length = ntohl(msg_length);
				char msg[msg_length];
				r = protocol_receive(&(self->protocol), &(msg[0]), msg_length);
				printf("print msg: %s\n", msg);
			}
		}
	}
	if (s == EXIT_CODE){
		s = 0; // execution was successful
	}
	return s;
}

//finalize the client
void client_shutdown(client_t* self){
	protocol_release(&(self->protocol));
	freeaddrinfo(self->result);
}