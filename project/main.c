#define _POSIX_C_SOURCE 200112L
#include "client_main.h"
#include "server_main.h"

#define CLIENT "client"
#define SERVER "server"

int Client(const char* host, const char* service){
	networkcomp_t client;
	int s = network_component_start(&client, host, service, false);
	if (s != -1){
		s = client_network_component_connect(&client);
	} 
	if (s != -1){ // if it could not connect
		s = client_network_component_play(&client);
	}
	network_component_shutdown(&client);
	return s;
}

int Server(const char* service){
	networkcomp_t server;
	int s = network_component_start(&server, 0, service, true);
	if (s != -1){
		s = server_network_component_listen_for_client(&server);
	}
	if (s != 1){
		s = server_network_component_play(&server);
	}
	network_component_shutdown(&server);
	return s;
}

int main(int argc, char* argv[]) {
	int s = 1;

	if (argc > 1 && strcmp(argv[1], CLIENT) == 0){
		if (argc == 4){
			s = Client(argv[2], argv[3]);
		} else {
			s = 1;
			printf("Uso: ./tp client <host> <puerto>\n");
		}
	} else if (argc > 1 && strcmp(argv[1], SERVER) == 0){
		if (argc == 3){
			s = Server(argv[2]);
		} else {
			s = 1;
			printf("Uso: ./tp server <puerto>\n");
		}
	} else {
		printf("Modo no soportado, el primer parámetro debe ser server o client\n");
	}
	if (s == -1){
		s = 1;
	}
    return s;
}
