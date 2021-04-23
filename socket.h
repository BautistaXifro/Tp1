
#ifndef __SOCKET_H__
#define __SOCKET_H__

#define _POSIX_C_SOURCE 201112L  // Habilita getaddrinfo
#include <arpa/inet.h>           // inet_ntop
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct socket {
  int fd;
} socket_t;

void socket_init(socket_t* self);

int socket_connect(socket_t* self, const char* hostname, const char* port);

int socket_bind(socket_t* self, const char* port);

int socket_accept(socket_t* self, socket_t* server);

int socket_send(socket_t* self, const unsigned char* mensaje, unsigned int messageLength);

int socket_receive(socket_t* self, unsigned char* buffer, unsigned int bufferLength);

void socket_close(socket_t* self);

#endif