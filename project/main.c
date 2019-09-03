#define _POSIX_C_SOURCE 200112L
#include "client_main.h"
#include "server_main.h"

#define CLIENT "client"
#define SERVER "server"

int Client(const char* host, const char* service){
	networkcomp_t client;
	int s = network_component_start(&client, host, service, false);
	if (client_network_component_connect(&client) != -1) {
		s = client_network_component_play(&client);
	}
	network_component_shutdown(&client);
	return s;
}

int Server(const char* service){
	networkcomp_t server;
	int s = network_component_start(&server, 0, service, true);
	server_network_component_listen_for_client(&server);
	return s;
}

int main(int argc, char* argv[]) {
	const char* port = "7777";
	const char* host = "localhost";

	if (argc > 1 && strcmp(argv[1], CLIENT) == 0){
		Client(host, port);
	} else if (argc > 1 && strcmp(argv[1], SERVER) == 0){
		Server(port);
	} else {
		printf("Invalid mode, first parameter mus be one of the following\n");
		printf("server\n");
		printf("client\n");
	}
    return 0;
}