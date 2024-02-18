#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>

#define PORT 8080

typedef struct {
	int clientSocket;
	pthread_t threadId;
} ClientInfo;

void enable_server();

#endif
