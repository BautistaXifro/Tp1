#include "server.h"
#include "hill_cipher.h"
#include <math.h>

void server_init(server_t* self, char* port){
    if(self == NULL){
        printf("Error al crear el servidor, self es nulo.");
        return;
    }

    socket_init(&self->server_socket);
    if (socket_bind(&self->server_socket, port)) {
        printf("Error al crear el servidor");
        return;
    }

    socket_init(&self->client_socket);
    if (socket_accept(&self->client_socket, &self->server_socket)) {
        printf("Error al aceptar un cliente");
        socket_close(&self->server_socket);
        return;
    }
}


void server_cipher_message(server_t* self, char* key){
    if (self == NULL) return;

    hill_cipher_t cipher;
    hill_init(&cipher, key);
    int buff_length;
    int bytes_received = 0;
    int numeric_msg_length;
    unsigned char buf[6];

    while (bytes_received = socket_receive_msg(&self->client_socket, buf)) {
        int* numeric_msg;
        hill_filter_message(buf);
        numeric_msg_length = hill_calculate_dimension(&cipher, buf);
        numeric_msg = malloc(numeric_msg_length * sizeof(int));
        hill_cipher(&cipher, buf, numeric_msg);
        server_send(self->client_socket, numeric_msg, numeric_msg_length);
        free(numeric_msg);
    }

    hill_destroy(&cipher);
    server_close(self);
}


void server_send(server_t* self, int* numeric_msg, int msg_length){
    if(self == NULL) return;

    int bytes_send = 0;

    socket_send_numeric(&self->client_socket, numeric_msg, msg_length);

}

void server_close(server_t* self){
    if (self == NULL) {
    printf("Error al cerrar el servidor, self es nulo.");
    return;
    }

    socket_close(&self->client_socket);
    socket_close(&self->server_socket);
}