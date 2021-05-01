#include "client.h"

int main(int argc, char* argv[]){
    
    if(argc < 4){
        printf("El cliente tiene formato ./client server_name port filepath\n");
        return -1;
    }

    client_t client;

    client_init(&client, argv[1], argv[2]);

    client_send(&client, argv[3]);

    client_close(&client);

    return 0;
}