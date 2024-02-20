#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "chess.h"
#include "server.h"

ClientInfo clients[2];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(char *message, int socket) {
	for (int i = 0; i < 2; i++) {
		if (clients[i].socket != socket) {
			if (send(clients[i].socket, message, strlen(message), 0) == -1) {
				perror("Send failed");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void *handle_client(void *client_info) {
	ClientInfo *info = (ClientInfo*)client_info;
	int socket = info->socket;
	char buffer[MAX_BUFFER_SIZE];

	while(1) {
		memset(buffer, 0, sizeof(buffer));

		if (recv(socket, buffer, sizeof(buffer), 0) == -1) {
			perror("Receive failed");
			break;
		}

		pthread_mutex_lock(&mutex);
		broadcast_message(buffer, socket);
		pthread_mutex_unlock(&mutex);
	}

	close(socket);
	pthread_exit(NULL);
}

void* enable_server() {
	srand(time(0));
	bool color = rand() % 2;
	int server_socket;
	struct sockaddr_in server_addr;
	socklen_t addr_size = sizeof(struct sockaddr_in);

	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket creation failed");
		return NULL;
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("Binding failed");
		return NULL;
	}

	if (listen(server_socket, 2) == -1) {
		perror("Listening failed");
		return NULL;
	}

	printf("Server listening on port %d...\n", PORT);

	for (int i = 0; i < 2; i++) {
		if ((clients[i].socket = accept(server_socket, (struct sockaddr*)&server_addr, &addr_size)) == -1) {
			perror("Acceptance failed");
			return NULL;
		}

		printf("Connection accepted from %s:%d\n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port));

		if (pthread_create(&clients[i].thread_id, NULL, handle_client, (void*)&clients[i]) != 0) {
			perror("Thread creation failed");
			return NULL;
		}
		send(clients[i].socket, &color, sizeof(color), 0);
		color = !color;
	}

	for (int i = 0; i < 2; i++) {
		pthread_join(clients[i].thread_id, NULL);
	}

	close(server_socket);
	return NULL;
}

void start_server() {
	pthread_t tid;
	if (pthread_create(&tid, NULL, enable_server, NULL) != 0) {
		perror("pthread_create");
		exit(EXIT_FAILURE);
	}
	sleep(1.0);
}

void *receive_move(void *d) {
	ClientData* data = (ClientData*)d;
	char buffer[MAX_BUFFER_SIZE];

	while (1) {
		memset(buffer, 0, sizeof(buffer));

		if (recv(data->socket, buffer, sizeof(buffer), 0) == -1) {
			perror("Receive failed");
			exit(EXIT_FAILURE);
		}
		play_move(data->chess, buffer);
	}
	pthread_exit(NULL);
}

void connect_to_server(ClientData* data) {
	struct sockaddr_in server_addr;

	if ((data->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(data->ip_address);
	server_addr.sin_port = htons(PORT);

	if (connect(data->socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("Connection failed");
		exit(EXIT_FAILURE);
	}

	printf("Connected to the server\n");
	recv(data->socket, &data->color, sizeof(data->color), 0);
	printf("Player color: %s\n", data->color ? "white" : "black");

	if (pthread_create(&data->thread_id, NULL, receive_move, (void*)data) != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
}

void send_move(ClientData data, const char move[]) {
	if (send(data.socket, move, strlen(move), 0) == -1) {
		perror("Send failed");
		exit(EXIT_FAILURE);
	}
}

void disconnect(ClientData data) {
	close(data.socket);
}
