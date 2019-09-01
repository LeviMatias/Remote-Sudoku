#include "server_main.h"

void server_start(server_t* self, const char* hostname, const char* servicename){

	memset(&(self->hints), 0, sizeof(self->hints));
	self->hints.ai_family = AF_INET;       /* IPv4 */
	self->hints.ai_socktype = SOCK_STREAM; /* TCP */
	self->hints.ai_flags = AI_PASSIVE;
	//check host name
	int s = getaddrinfo(hostname, servicename, &(self->hints), &(self->result));
	if (s != 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      return;
   }
   socket_init(&(self->socket),self->result);
}

//finalize the server
void server_shutdown(server_t* self){

}