#ifndef __SERVER_H__
#define __SERVER_H__
#include "common_socket.h"

typedef struct server {
  socket_t server_socket;
  socket_t client_socket;
} server_t;

void server_init(server_t* self, char* port);

void server_cipher_message(server_t* self,char* key);

void server_send(server_t* self, int* numeric_msg, int msg_length);

void server_close(server_t* self);

#endif
