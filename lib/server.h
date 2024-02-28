#ifndef SERVER_H
#define SERVER_H

#include "chess.h"
#include <pthread.h>

#define MAX_BUFFER_SIZE 5

typedef struct {
	Chess* chess;
	bool color;
	int socket;
	pthread_t thread_id;
	char ip_address[15];
	char port[5];
	char room_id[10];
} ClientData;

typedef struct {
	int socket;
	pthread_t thread_id;
} ClientInfo;

int connect_to_server(ClientData* data);
void disconnect(ClientData* data);
void send_move(ClientData* data, const char move[]);

#endif
