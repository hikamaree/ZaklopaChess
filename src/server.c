
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "server.h"

void send_move(ClientData* data, const char move[]) {
	if (send(data->socket, move, strlen(move), 0) == -1) {
		perror("Send failed");
	}
}

void *receive_message(void *arg) {
	ClientData *data = (ClientData*)arg;
	char buffer[MAX_BUFFER_SIZE];

	while (1) {
		memset(buffer, 0, sizeof(buffer));

		ssize_t bytes_received = recv(data->socket, buffer, sizeof(buffer), 0);
		if (bytes_received == -1) {
			perror("Receive failed");
			break;
		} else if (bytes_received == 0) {
			break;
		}

		play_move(data->chess, buffer);
		printf("%s\n", buffer);
	}

	close(data->socket);
	pthread_exit(NULL);
}

int connect_to_server(ClientData* data) {
	if ((data->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket creation failed");
		return 0;
	}

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(data->port));
	if (inet_pton(AF_INET, data->ip_address, &server_addr.sin_addr) <= 0) {
		perror("Invalid address");
		return 0;
	}
	if (connect(data->socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("Connection failed");
		return 0;
	}

	printf("Connected to server\n");

	if (send(data->socket, data->room_id, strlen(data->room_id), 0) == -1) {
		perror("Send failed");
		return 0;
	}

	recv(data->socket, &data->color, sizeof(data->color), 0);
	printf("Player color: %s\n", data->color ? "white" : "black");

	if (pthread_create(&(data->thread_id), NULL, receive_message, data) != 0) {
		perror("Thread creation failed");
		return 0;
	}

	return 1;
}

void disconnect(ClientData* data) {
	close(data->socket);
	pthread_cancel(data->thread_id);
}
