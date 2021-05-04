#include "common_socket.h"
#include <stdlib.h>

void socket_init(socket_t* self) {
    if (self == NULL){
        printf("Error socket es nulo");
        return;
    }
    self->fd = -1; 
}

int _getaddrinfo(struct addrinfo** serv_info, const char* hostname,
                const char* port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int error = getaddrinfo(hostname, port, &hints, serv_info);
    if (error) {
    printf("Error getaddrinfo.");
    return -1;
    }

    return 0;
}

int socket_connect(socket_t* self, const char* hostname, const char* port) {
    if (self == NULL || port == NULL || hostname == NULL) return -1;
    struct addrinfo* serv_info;

    if (_getaddrinfo(&serv_info, hostname, port)) {
        return -1;
    }

    struct addrinfo* head = serv_info;
    int connected = 0;

    for (; serv_info && !connected; serv_info = serv_info->ai_next) {
        self->fd = socket(serv_info->ai_family, serv_info->ai_socktype,
                        serv_info->ai_protocol);
        if (connect(self->fd, serv_info->ai_addr,
                    serv_info->ai_addrlen) == -1) {
            close(self->fd);
        } else {
            connected = 1;
        }
    }
    if (self->fd == -1) {
        fprintf(stderr, "Unable to connect\n");
        return -1;
    }

    freeaddrinfo(head);
    return 0;
}

int socket_bind(socket_t* self, const char* port) {
    if (self == NULL || port == NULL) return -1;
    struct addrinfo* serv_info;

    if (_getaddrinfo(&serv_info, NULL, port)) {
        return -1;
    }

    int connected = 0;
    struct addrinfo* head = serv_info;

    for (; serv_info && !connected; serv_info = serv_info->ai_next) {
        self->fd = socket(serv_info->ai_family, serv_info->ai_socktype,
                         serv_info->ai_protocol);

        int val = 1;
        setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

        if (bind( self->fd, serv_info->ai_addr, serv_info->ai_addrlen) < 0){
            perror("bind");
            printf("%sn \n",strerror(errno));
        } else {
            connected = 1;
        }
    }

    listen(self->fd, 10);
    freeaddrinfo(head);

    return 0;
}

int socket_accept(socket_t* self, socket_t* server) {
    if (self == NULL || server == NULL) return -1;

    struct sockaddr_in address;
    socklen_t address_length = (socklen_t)sizeof(address);

    int fd = accept(server->fd, (struct sockaddr*)&address, &address_length);
    if (fd < 0){
        perror("acept");
        printf("%sn",strerror(errno));
    }
    self->fd = fd;

    return fd == -1;
}

int socket_receive(socket_t* self, unsigned char* buffer, int msg_length){
    if (self == NULL || buffer == NULL) return -1;
    
    int bytes_received = 0;
    int max_bytes = msg_length;

    while (bytes_received < msg_length) {
        int bytes = recv(self->fd, &buffer[bytes_received], max_bytes, 0);

        if (bytes == -1) {
            perror("receive_msg");
            printf("%sn",strerror(errno));
            return -1;
        }

        if (bytes == 0) {
            break;
        }

        bytes_received += bytes;
        max_bytes -= bytes;
    }

    buffer[bytes_received] = 0;

    return bytes_received;
}

int socket_send(socket_t* self, const unsigned char* msg,
                unsigned int msg_length) {
    if (self == NULL || msg == NULL) return -1;

    if (msg_length == 0) {
        return 0;
    }

    int bytes_pending = msg_length;
    int total_send = 0;

    while (total_send < msg_length) {
        int bytes = send(self->fd, &msg[total_send],
                         bytes_pending, MSG_NOSIGNAL);

        if (bytes == -1 || bytes == 0) {
            break;
        }

        total_send += bytes;
        bytes_pending -= bytes;
    }

    return total_send;
}

void socket_close(socket_t* self) {
    if (!self || self->fd == -1) {
    return;
    }

    shutdown(self->fd, SHUT_RDWR);
    close(self->fd);

    self->fd = -1;
}
