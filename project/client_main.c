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
	int s = 0;
	s = protocol_init(&(self->protocol), self->result);
	if (s != -1){
		char word[12+1];
		while (fgets(word, sizeof(word), stdin) && s != EXIT_CODE){
			int s = protocol_parse_client_input(&(self->protocol), word);
			if (s == 0){
				protocol_send(&(self->protocol));
				//protocol_receive(&(self->protocol));
			}
		}
		if (s == EXIT_CODE){
			s = 0; // execution was successful
		}
	} else{
		printf("Could not connect \n");
	}
	return s;
}

//finalize the client
void client_shutdown(client_t* self){
	protocol_release(&(self->protocol));
	freeaddrinfo(self->result);
}