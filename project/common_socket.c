#define _POSIX_C_SOURCE 200112L

#include "common_socket.h"

#include <errno.h>
#include <string.h>

const int socket_connect(int skt, const struct addrinfo* ptr){
	int s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
     if (s == -1) {
        printf("Error in connection: %s\n", strerror(errno));
        close(skt);
     } else {
     	printf("connected");
     } 
	return s;
}

int socket_init(socket_t* self, struct addrinfo* ai){
	int skt = 0;
	int are_we_connected = -1;
	struct addrinfo* ptr;

	for (ptr = ai; ptr != NULL && are_we_connected == -1; ptr = ptr->ai_next) {
      skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
      if (skt == -1) {
         printf("Error in socket init: %s\n", strerror(errno));
      } else {
      	 self->fd = skt;
         are_we_connected = socket_connect(skt,ptr);
         self->connected = are_we_connected;
      }
   }
   return are_we_connected;
}

bool socket_is_connected(socket_t* self){
	return (self->connected == CONNECTED);
}

void socket_release(socket_t* self){
	if (socket_is_connected(self)){
		close(self->fd);
	}
}