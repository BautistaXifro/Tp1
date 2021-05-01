#ifndef __CLIENTS_H__
#define __CLIENTS_H__
#include "common_socket.h"

typedef struct client {
  socket_t socket;
} client_t;

int client_init(client_t* self, char* server_name, char* port);

int client_send(client_t* self, char* file_name);

void client_close(client_t* self);

#endif