#include "server.h"
#include <stdlib.h>



int main(int argc, char* argv[]) {

	if(argc < 3){
		printf("El servidor tiene formato ./server port key\n");
		return -1;
	}

	server_t server;

	server_init(&server, argv[1]);

	server_cipher_message(&server, argv[2]);

	server_close(&server);

	return 0;
}