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
   socket_init(&(self->socket),self->result);
}

//attemps to connect and starts listening for input
//POS: returns exit value
int client_connect(client_t* self){
	return 0;
}

//finalize the client
void client_shutdown(client_t* self){
	freeaddrinfo(self->result);
}