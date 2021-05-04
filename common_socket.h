
#ifndef __COMMON_SOCKET_H__
#define __COMMON_SOCKET_H__


#include <arpa/inet.h>           // inet_ntop
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

typedef struct socket {
  int fd;
} socket_t;

void socket_init(socket_t* self);

int socket_connect(socket_t* self, const char* hostname, const char* port);

int socket_bind(socket_t* self, const char* port);

int socket_accept(socket_t* self, socket_t* server);

int socket_send(socket_t* self, const unsigned char* msg,
                unsigned int msg_length);

int socket_receive(socket_t* self, unsigned char* buffer, int max_bytes);

void socket_close(socket_t* self);


#endif
