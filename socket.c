#include "socket.h"

void socket_init(socket_t* self) {
    if(self == NULL){
        printf("Error socket es nulo");
        return;
    }
    self->fd = -1; 
}

int _getaddrinfo(struct addrinfo** serv_info, const char* hostname, const char* port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int error = getaddrinfo(hostname, port, &hints, serv_info);
    if (error) {
    printf("Error getaddrinfo.");
    return 1;
    }

    return 0;
}

int socket_connect(socket_t* self, const char* hostname, const char* port) {
    if (self == NULL || port == NULL || hostname == NULL) return -1;
    struct addrinfo* serv_info;

    if (_getaddrinfo(&serv_info, hostname, port)) {
        return 1;
    }

    struct addrinfo* head = serv_info;
    int connected = 0;

    for (; serv_info && !connected; serv_info = serv_info->ai_next) {
        self->fd = socket(serv_info->ai_family, serv_info->ai_socktype, serv_info->ai_protocol);
        if (connect(self->fd, serv_info->ai_addr, serv_info->ai_addrlen) == -1) {
            close(self->fd);
        } else {
            connected = 1;
        }
    }

    freeaddrinfo(head);
    return 0;
}