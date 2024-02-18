#ifndef CLIENT_H
#define CLIENT_H

#include "chess.h"
#include <pthread.h>

typedef struct {
	Chess* chess;
	int clientSocket;
	pthread_t receiveThreadId;
	char ip_address[20];
	bool color;
} ClientData;

void start_server();
void connect_to_server(ClientData* data);
void disconnect(ClientData data);
void send_move(ClientData data, const char move[]);

#endif
