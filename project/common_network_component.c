#include "common_network_component.h"

int network_component_start(networkcomp_t* self, const char* host,\
							 const char* service, bool is_passive){
	memset(&(self->hints), 0, sizeof(self->hints));
	self->hints.ai_family = AF_INET;       /* IPv4 */
	self->hints.ai_socktype = SOCK_STREAM; /* TCP */
	if (is_passive){
		self->hints.ai_flags = AI_PASSIVE;
	} else {
		self->hints.ai_flags = 0;
	}
	//check host name
	int s = getaddrinfo(host, service, &(self->hints), &(self->result));
	if (s != 0) { 
      printf("Error in getaddrinfo: %s\n", gai_strerror(s));
   }
   return s;
}

//finalize the server
void network_component_shutdown(networkcomp_t* self){
	protocol_release(&(self->protocol));
	freeaddrinfo(self->result);
}
