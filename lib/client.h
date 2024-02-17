#ifndef SERVER_H
#define SERVER_H

#include "chess.h"
#include <bits/pthreadtypes.h>

typedef struct {
	Chess* chess;
	int clientSocket;
	pthread_t receiveThreadId;
	bool color;
} ClientData;

void start_server();
void connect_to_server(ClientData* data);
void disconnect(ClientData data);
void send_move(ClientData data, const char move[]);

#endif
