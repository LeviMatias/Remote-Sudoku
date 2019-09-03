#include "client_main.h"

int main(int argc, char* argv[]) {
	client_t client;
	const char* port = "7777";
	client_start(&client,"localhost",port);
	if (client_connect(&client) != -1) {
		client_play(&client);
	}
	client_shutdown(&client);
    return 0;
}