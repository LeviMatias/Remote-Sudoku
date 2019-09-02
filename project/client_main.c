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

//attemps to connect and starts listening for input
//POS: returns exit value
int client_connect(client_t* self){
	int s = 0;
	s = socket_init(&(self->socket),self->result);
	if (s != -1){
		char word[12+1];
		if (fgets(word, sizeof(word), stdin)){
			protocol_parse_client_input(&(self->protocol),word);
			socket_send(&(self->socket), (self->protocol.msg), (self->protocol.msg_size));
		}
	}
	return s;
}

//finalize the client
void client_shutdown(client_t* self){
	socket_release(&(self->socket));
	freeaddrinfo(self->result);
}