#ifndef __CLIENTS_H__
#define __CLIENTS_H__
#include "common_socket.h"

typedef struct client {
  socket_t socket;
} client_t;

int client_init(client_t* self, char* server_name, char* port);

int client_send(client_t* self, char* file_name);

int client_receive_length_msg(client_t* self);

void client_send_length_msg(client_t* self, int length);

void client_receive_numeric(client_t* self, int* cipher_numeric_msg, int length_numeric_msg);

void char_maping(unsigned char* string, int* array, int size);

void client_close(client_t* self);

#endif