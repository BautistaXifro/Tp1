#include "hill_cipher.h"
#include "common_file_reader.h"
#include "client.h"

#define BUF_MAX_LEN 64

int client_init(client_t* self, char* server_name, char* port) {
    if(self == NULL) return -1;
    socket_init(&self->socket);

    if (socket_connect(&self->socket, server_name, port)) {
        printf("Error al conectarse al servidor.");
        return -1;
    }

    return 0;
}

int client_send(client_t* self,char* file_name){
    if (!self) {
        return -1;
    }
    
    int bytes_receive;
    file_reader_t file_reader;
    file_reader_init(&file_reader, file_name);

    unsigned char msg[BUF_MAX_LEN];

    while (!file_reader_eof(&file_reader)) {
        int* cipher_numeric_msg;
        int bytes_read = file_reader_read(&file_reader, msg, BUF_MAX_LEN);

        if (bytes_read == -1) {
            printf("Error al leer el archivo\n");
            return -1;
        }
        
        socket_send_msg(&self->socket, msg, bytes_read);
        short length_numeric_msg = socket_receive_length(&self->socket);
        cipher_numeric_msg = malloc(length_numeric_msg * sizeof(int));
        bytes_receive = socket_receive_numeric(&self->socket, cipher_numeric_msg, length_numeric_msg);
        hill_char_maping(msg,cipher_numeric_msg, bytes_receive);
        free(cipher_numeric_msg);
        printf("%s", msg);
    }

    file_reader_destroy(&file_reader);
    client_close(self);
    return 0;
}


void client_close(client_t* self) {
    if (self) {
        socket_close(&self->socket);
    }
}