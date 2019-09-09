#ifndef __MESSAGE_H__
#define __MESSAGE_H__
#include <stdio.h>

#define MAX_MESSAGE_LENGTH 722 //in bytes

typedef struct{
	char text[MAX_MESSAGE_LENGTH + 1];
	size_t size;
} common_message_t;

#endif
