#include "client_file_reader.h"
#include "client.h"
#include <stdlib.h>

#define BUF_MAX_LEN 255
#define LENGTH_MSG 2

int client_init(client_t* self, char* server_name, char* port) {
    if (self == NULL) return -1;
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
    file_reader_t file_reader;
    file_reader_init(&file_reader, file_name);

    unsigned char msg[BUF_MAX_LEN];

    while (file_reader_read(&file_reader, (char *) msg, BUF_MAX_LEN) == 0) {
        int* cipher_numeric_msg;
        
        int aux =  strlen((char *) msg);
        client_send_length_msg(self,aux);
        socket_send(&self->socket, msg, aux);
        //RECEIVE----------------------------------------
        int length_numeric_msg = client_receive_length_msg(self);
        cipher_numeric_msg = malloc(length_numeric_msg * sizeof(int));
        client_receive_numeric(self, cipher_numeric_msg, length_numeric_msg);
        memset(msg, 0, sizeof(msg));
        char_maping(msg,cipher_numeric_msg, length_numeric_msg);
        free(cipher_numeric_msg);
        printf("%s", msg);
        memset(msg, 0, sizeof(msg));
    }
    file_reader_destroy(&file_reader);
    client_close(self);
    return 0;
}

void client_receive_numeric(client_t* self, int* cipher_numeric_msg,
                            int length_numeric_msg){
    unsigned char buffer[sizeof(uint32_t)];
    for (int i = 0; i < length_numeric_msg; i++){
        socket_receive(&self->socket, buffer, sizeof(uint32_t));
        uint32_t aux = *(uint32_t*)(buffer);
        cipher_numeric_msg[i] = (int) ntohl((uint32_t) aux);
    }
}

void client_send_length_msg(client_t* self, int length){
    uint16_t msg_length = length;
    msg_length = htons(msg_length);
    unsigned char buffer[sizeof(msg_length)];

    memcpy(buffer, (char*)&msg_length,sizeof(uint16_t));

    socket_send(&self->socket, buffer, sizeof(uint16_t));
}

int client_receive_length_msg(client_t* self){
    unsigned char buffer[sizeof(uint16_t)];
    if (socket_receive(&self->socket, buffer, LENGTH_MSG) <= 0){
        return -1;
    }
    uint16_t max_bytes = *(uint16_t*)(buffer);
    max_bytes = ntohs(max_bytes);

    return (int) max_bytes;
}

void char_maping(unsigned char* string, int* array, int size){
    for (int i = 0; i < size; i++){
        string[i + 1] = '\n';
        switch (array[i])
        {
        case 0:
            string[i] = 'A';
            break;

        case 1:
            string[i] = 'B';
            break;
        
        case 2:
            string[i] = 'C';
            break;

        case 3:
            string[i] = 'D';
            break;

        case 4:
            string[i] = 'E';
            break;

        case 5:
            string[i] = 'F';
            break;

        case 6:
            string[i] = 'G';
            break;
                
        case 7:
            string[i] = 'H';
            break;
          
        case 8:
            string[i] = 'I';
            break;
            
        case 9:
            string[i] = 'J';
            break;
          
        case 10:
            string[i] = 'K';
            break;
                
        case 11:
            string[i] = 'L';
            break;
                
        case 12:
            string[i] = 'M';
            break;
                
        case 13:
            string[i] = 'N';
            break;
         
        case 14:
            string[i] = 'O';
            break;
 
        case 15:
            string[i] = 'P';
            break;
        
        case 16:
            string[i] = 'Q';
            break;
        
        case 17:
            string[i] = 'R';
            break;
        
        case 18:
            string[i] = 'S';
            break;
 
        case 19:
            string[i] = 'T';
            break;
           
        case 20:
            string[i] = 'U';
            break;
             
        case 21:
            string[i] = 'V';
            break;
          
        case 22:
            string[i] = 'W';
            break;
                
        case 23:
            string[i] = 'X';
            break;
                
        case 24:
            string[i] = 'Y';
            break;
                
        case 25:
            string[i] = 'Z';
            break;

        default:
            printf("Error no es un int\n"); 
            break;
        } 
    }
}

void client_close(client_t* self) {
    if (self) {
        socket_close(&self->socket);
    }
}
