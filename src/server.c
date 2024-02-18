#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_BUFFER_SIZE 1024

ClientInfo clients[2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcastMessage(char *message, int senderSocket) {
	for (int i = 0; i < 2; i++) {
		if (clients[i].clientSocket != senderSocket) {
			if (send(clients[i].clientSocket, message, strlen(message), 0) == -1) {
				perror("Send failed");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void *handleClient(void *clientInfo) {
	ClientInfo *info = (ClientInfo*)clientInfo;
	int clientSocket = info->clientSocket;
	char buffer[MAX_BUFFER_SIZE];

	while (1) {
		memset(buffer, 0, sizeof(buffer));

		if (recv(clientSocket, buffer, sizeof(buffer), 0) == -1) {
			perror("Receive failed");
			exit(EXIT_FAILURE);
		}

		pthread_mutex_lock(&mutex);
		broadcastMessage(buffer, clientSocket);
		pthread_mutex_unlock(&mutex);
	}

	close(clientSocket);
	pthread_exit(NULL);
}

void enable_server() {
	srand(time(0));
	bool color = rand() % 2;
	int serverSocket;
	struct sockaddr_in serverAddr;
	socklen_t addrSize = sizeof(struct sockaddr_in);

	if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(PORT);

	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
		perror("Binding failed");
		exit(EXIT_FAILURE);
	}

	if (listen(serverSocket, 2) == -1) {
		perror("Listening failed");
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d...\n", PORT);

	for (int i = 0; i < 2; i++) {
		if ((clients[i].clientSocket = accept(serverSocket, (struct sockaddr*)&serverAddr, &addrSize)) == -1) {
			perror("Acceptance failed");
			exit(EXIT_FAILURE);
		}

		printf("Connection accepted from %s:%d\n", inet_ntoa(serverAddr.sin_addr), ntohs(serverAddr.sin_port));

		if (pthread_create(&clients[i].threadId, NULL, handleClient, (void*)&clients[i]) != 0) {
			perror("Thread creation failed");
			exit(EXIT_FAILURE);
		}
		send(clients[i].clientSocket, &color, sizeof(color), 0);
		color = !color;
	}

	for (int i = 0; i < 2; i++) {
		pthread_join(clients[i].threadId, NULL);
	}

	close(serverSocket);
}
