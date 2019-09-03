#include "client_main.h"
#include "server_main.h"

#define CLIENT "client"
#define SERVER "server"

int main(int argc, char* argv[]) {

	if (argc > 1 && strcmp(argv[1], CLIENT) == 0){
		client_t client;
		const char* port = "7777";
		client_start(&client,"localhost",port);
		if (client_connect(&client) != -1) {
			client_play(&client);
		}
		client_shutdown(&client);
	} else if (argc > 1 && strcmp(argv[1], SERVER) == 0){

	} else {
		printf("Invalid mode, first parameter mus be one of the following\n");
		printf("server\n");
		printf("client\n");
	}
    return 0;
}