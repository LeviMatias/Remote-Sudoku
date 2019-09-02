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

int socket_send(socket_t* self, const char* buffer, size_t size){
  int sent = 0;
  int s = 0;
  bool is_the_socket_valid = true;
  //printf("size: %zu\n", size);
  //printf("msg: %s\n", buffer);
  while (sent < size && is_the_socket_valid) {
    s = send(self->fd, &buffer[sent], size-sent, MSG_NOSIGNAL);

    if (s == 0) {
       is_the_socket_valid = false;
    } else if (s == -1) {
       is_the_socket_valid = false;
    } else {
       sent += s;
    }
  }

  if (is_the_socket_valid) {
    return size;
  } else {
    return -1;
  }
}

int socket_bind_and_listen(socket_t* self, struct addrinfo* ai){
  int s = -1;
  struct addrinfo* ptr;

  for (ptr = ai; ptr != NULL && s == -1; ptr = ptr->ai_next) {
    s = bind(self->fd, ptr->ai_addr, ptr->ai_addrlen);
  }

  if (s != -1){
    s = listen(self->fd, 1);
  }

  if (s == -1){
    printf("Error: %s\n", strerror(errno));
  }
  return s;
}

int socket_accept(socket_t* self, struct addrinfo* ai){
  return accept(self->fd, NULL, NULL);
}

int socket_receive(socket_t* self, char* buffer, size_t size){
  int received = 0;
  int s = 0;
  bool is_the_socket_valid = true;

  while (received < size && is_the_socket_valid) {
    s = recv(self->fd, &buffer[received], size-received, 0);

    if (s == 0) { // socket is closed
      is_the_socket_valid = false;
    } else if (s == -1) { // there was an error
      is_the_socket_valid = false;
      printf("Error: %s\n", strerror(errno));
    } else {
      received += s;
    }
  }

  if (is_the_socket_valid) {
    return received;
  } else {
    return -1;
  }
}

void socket_release(socket_t* self){
	if (socket_is_connected(self)){
		close(self->fd);
	}
}