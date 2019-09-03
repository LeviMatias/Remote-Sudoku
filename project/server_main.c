#include "server_main.h"

void server_start(server_t* self, const char* hostname, const char* servicename){

	memset(&(self->hints), 0, sizeof(self->hints));
	self->hints.ai_family = AF_INET;       /* IPv4 */
	self->hints.ai_socktype = SOCK_STREAM; /* TCP */
	self->hints.ai_flags = AI_PASSIVE;
	//check host name
	int s = getaddrinfo(0, servicename, &(self->hints), &(self->result));
	if (s != 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
      return;
   }
}

int server_listen_for_client(server_t* self){
	int s = protocol_init(&(self->protocol), self->result);
	s = protocol_bind_and_listen(&(self->protocol), self->result);
	s = protocol_accept_connection(&(self->protocol), self->result);

	while (s != -1){
		s = protocol_receive(&(self->protocol), &(self->protocol.msg[0]), 1);
		printf("success\n");
		//s = protocol_process_command();
	}
	return s;
}

//finalize the server
void server_shutdown(server_t* self){
	protocol_release(&(self->protocol));
	freeaddrinfo(self->result);
}