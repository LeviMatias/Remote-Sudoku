#include "common_socket.h"

#include <errno.h>
#include <string.h>

int socket_init(socket_t* self, struct addrinfo* ai){
	int skt = 0;
  self->connected = NOT_CONNECTED;

  skt = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  if (skt == -1) {
     printf("Error in socket init: %s\n", strerror(errno));
  } else {
  	 self->fd = skt;
  }
  return skt;
}

int socket_connect(socket_t* self, struct addrinfo* ptr){
  int s = connect(self->fd, ptr->ai_addr, ptr->ai_addrlen);
   if (s == -1) {
      printf("Error in connection: %s\n", strerror(errno));
      close(self->fd);
   } else {
    self->connected = self->fd;
    printf("connected\n");
   } 
  return s;
}

bool socket_is_connected(socket_t* self){
	return (self->connected != NOT_CONNECTED);
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

  int val = 1; //configure socket to reuse address if TIME WAIT
  setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

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
  int fd = accept(self->fd, NULL, NULL);
  if (fd != -1){
    self ->connected = fd;
  }
  return fd;
}

int socket_receive(socket_t* self, char* buffer, size_t size){
  int received = 0;
  int s = 0;
  int is_the_socket_valid = 1;

  while (received < size && is_the_socket_valid > 0 && self->connected != -1) {
    s = recv(self->connected, &buffer[received], size-received, 0);

    if (s == 0) { // socket is closed
      is_the_socket_valid = false;
    } else if (s == -1) { // there was an error
      is_the_socket_valid = false;
      printf("Error: %s\n", strerror(errno));
    } else {
      received += s;
    }
  }

  if (is_the_socket_valid > 0) {
    return received;
  } else {
    return is_the_socket_valid;
  }
}

void socket_release(socket_t* self){
	if (self->fd != -1){
    if (self->connected != -1 && shutdown(self->connected, SHUT_RDWR) == -1){
      printf("Closing connection error: %s\n", strerror(errno));
    }
		close(self->fd);
	}
}