#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <stdio.h>

typedef struct {
	int fd; //file descriptor
	char* host;
	char* service; //port
} socket_t;

void socket_init(socket_t* socket);

int socket_connect(socket_t* self,const char* host, const char* service);

int socket_bind_and_listen(socket_t* self, const char* service);

int socket_send(socket_t* self, const void* buffer, size_t length);

int socket_receive(socket_t* self, const void* buffer, size_t length);

void socket_release(socket_t* socket);

#endif