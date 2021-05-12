#include "client_file_reader.h"
#include "client.h"
#include <stdlib.h>

#define BUF_MAX_LEN 256
#define LENGTH_MSG 2
#define SIZE_OF_UNIT 4

int client_init(client_t* self, char* server_name, char* port) {
    if (self == NULL) return -1;
    socket_init(&self->socket);

    if (socket_connect(&self->socket, server_name, port)) {
        printf("Error al conectarse al servidor.");
        client_close(self);
        return -1;
    }

    return 0;
}

int client_send(client_t* self,char* file_name){
    if (!self) {
        return -1;
    }
    file_reader_t file_reader;
    file_reader_init(&file_reader, file_name);

    unsigned char msg[BUF_MAX_LEN];

    while (file_reader_read(&file_reader, (char *) msg, BUF_MAX_LEN) == 0) {
        int aux =  strlen((char *) msg);
        client_send_length_msg(self,aux);
        socket_send(&self->socket, msg, aux);
        //RECEIVE----------------------------------------
        int length_numeric_msg = client_receive_length_msg(self);
        int* cipher_numeric_msg = malloc(length_numeric_msg * sizeof(int));
        client_receive_numeric(self, cipher_numeric_msg, length_numeric_msg);
        memset(msg, 0, sizeof(msg));
        char_maping(msg,cipher_numeric_msg, length_numeric_msg);
        printf("%s", msg);
        memset(msg, 0, sizeof(msg));
        free(cipher_numeric_msg);
    }
    file_reader_destroy(&file_reader);
    client_close(self);
    return 0;
}

void client_receive_numeric(client_t* self, int* cipher_numeric_msg,
                            int length_numeric_msg){
    unsigned char buffer[SIZE_OF_UNIT];
    for (int i = 0; i < length_numeric_msg; i++){
        socket_receive(&self->socket, buffer, sizeof(buffer));
        uint32_t aux = *(uint32_t*)(buffer);
        cipher_numeric_msg[i] = (int) ntohl(aux);
    }
}

void client_send_length_msg(client_t* self, int length){
    uint16_t msg_length = length;
    msg_length = htons(msg_length);
    unsigned char buffer[sizeof(msg_length)];

    memcpy(buffer, (char*)&msg_length,sizeof(msg_length));

    socket_send(&self->socket, buffer, sizeof(buffer));
}

int client_receive_length_msg(client_t* self){
    unsigned char buffer[LENGTH_MSG];
    if (socket_receive(&self->socket, buffer, sizeof(buffer)) <= 0){
        return -1;
    }
    uint16_t max_bytes = *(uint16_t*)(buffer);
    max_bytes = ntohs(max_bytes);

    return (int) max_bytes;
}

void char_maping(unsigned char* string, int* array, int size){
    int i;
    for (i = 0; i < size; i++){
        char char_value = (char) (array[i] + 65);
        string[i] = char_value;
    }
    string[i] = '\n';
    string[i + 1] = '\0';
}

void client_close(client_t* self) {
    if (self) {
        socket_close(&self->socket);
    }
}
