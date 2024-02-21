#ifndef SERVER_H
#define SERVER_H

#include "chess.h"
#include <pthread.h>

#define PORT 4603
#define MAX_BUFFER_SIZE 8

typedef struct {
	Chess* chess;
	int socket;
	pthread_t thread_id;
	char ip_address[20];
	bool host;
	bool received;
	bool color;
} ClientData;

typedef struct {
	int socket;
	pthread_t thread_id;
} ClientInfo;

void start_server();
void disable_server();
void connect_to_server(ClientData* data);
void disconnect(ClientData* data);
void send_move(ClientData* data, const char move[]);

#endif
