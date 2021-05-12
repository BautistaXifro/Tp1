#include "server.h"
#include "server_hill_cipher.h"
#include <math.h>
#define BUF_MAX_LEN 255
#define LENGTH_MSG 2

void server_init(server_t* self, char* port){
    if (self == NULL){
        printf("Error al crear el servidor, self es nulo.");
        return;
    }

    socket_init(&self->server_socket);
    if (socket_bind(&self->server_socket, port)) {
        printf("Error al crear el servidor");
        return;
    }

    socket_init(&self->client_socket);
    if (socket_accept(&self->client_socket, &self->server_socket) < 0) {
        printf("Error al aceptar un cliente");
        socket_close(&self->server_socket);
        return;
    }
}


void server_cipher_message(server_t* self, char* key){
    if (self == NULL) return;

    hill_cipher_t cipher;
    hill_init(&cipher, key);
    int msg_received_length = 0;
    unsigned char buf[BUF_MAX_LEN];

    while ((msg_received_length = server_receive_length_msg(self)) > 0) {
        socket_receive(&self->client_socket, buf, msg_received_length);
        hill_filter_message((char *) buf);
        int numeric_msg_length = hill_calculate_dimension(&cipher, buf);
        int numeric_msg[numeric_msg_length];
        hill_cipher(&cipher, buf, numeric_msg);
        //SEND---------------------------------------------------
        server_send_length_msg(self, numeric_msg_length);
        server_send_numeric(self, numeric_msg, numeric_msg_length);
        memset(buf, 0 ,sizeof(buf));
    }
    hill_destroy(&cipher);
    server_close(self);
}


int server_receive_length_msg(server_t* self){
    unsigned char buffer[LENGTH_MSG];
    if (socket_receive(&self->client_socket, buffer, LENGTH_MSG) <= 0){
        return -1;
    }
    uint16_t max_bytes = *(uint16_t*)(buffer);
    max_bytes = ntohs(max_bytes);

    return (int) max_bytes;
}

void server_send_length_msg(server_t* self, int length){
    uint16_t msg_length = length;
    msg_length = htons(msg_length);
    unsigned char buffer[sizeof(msg_length)];
    memcpy(buffer, (char*)&msg_length,sizeof(msg_length));

    socket_send(&self->client_socket, buffer, sizeof(buffer));
}

void server_send_numeric(server_t* self, int* numeric_msg,
                        int numeric_msg_length){
    for (int i = 0; i < numeric_msg_length; i++){
        uint32_t send_int = htonl((uint32_t) numeric_msg[i]);
        unsigned char buffer[sizeof(send_int)];
        memcpy(buffer, (char*)&send_int,sizeof(send_int));

        socket_send(&self->client_socket, buffer, sizeof(buffer));
    }
}

void server_close(server_t* self) {
    if (self == NULL) {
        printf("Error al cerrar el servidor, self es nulo.");
        return;
    }

    socket_close(&self->client_socket);
    socket_close(&self->server_socket);
}
