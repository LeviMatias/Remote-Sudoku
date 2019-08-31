#include "client/client_main.h"

int main(int argc, char* argv[]) {
	client_t client;
	const char* port = "7777";
	client_start(&client,"localhost",port);
	//client_run();
	client_shutdown(&client);
    return 0;
}