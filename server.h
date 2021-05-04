#ifndef __SERVER_H__
#define __SERVER_H__
#include "common_socket.h"

typedef struct server {
  socket_t server_socket;
  socket_t client_socket;
} server_t;

void server_init(server_t* self, char* port);

void server_cipher_message(server_t* self,char* key);

int server_receive_length_msg(server_t* self);

void server_send_length_msg(server_t* self, int numeric_msg_length);

void server_send_numeric(server_t* self, int* numeric_msg,
                        int numeric_msg_length);

void server_close(server_t* self);

#endif
