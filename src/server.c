#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "chess.h"
#include "server.h"

#define PORT 8080
#define MAX_BUFFER_SIZE 8

void *receive_move(void *d) {
	ClientData* data = (ClientData*)d;
	char buffer[MAX_BUFFER_SIZE];

	while (1) {
		memset(buffer, 0, sizeof(buffer));

		if (recv(data->clientSocket, buffer, sizeof(buffer), 0) == -1) {
			perror("Receive failed");
			exit(EXIT_FAILURE);
		}
		play_move(data->chess, buffer);
		printf("%s", buffer);
	}
	pthread_exit(NULL);
}

void connect_to_server(ClientData* data) {
	struct sockaddr_in serverAddr;

	if ((data->clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddr.sin_port = htons(PORT);

	if (connect(data->clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		perror("Connection failed");
		exit(EXIT_FAILURE);
	}

	printf("Connected to the server\n");

	if (pthread_create(&data->receiveThreadId, NULL, receive_move, (void*)data) != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
}

void send_move(ClientData data, const char move[]) {
	if (send(data.clientSocket, move, strlen(move), 0) == -1) {
		perror("Send failed");
		exit(EXIT_FAILURE);
	}
}

void disconect(ClientData data) {
	close(data.clientSocket);
	pthread_join(data.receiveThreadId, NULL);
}
