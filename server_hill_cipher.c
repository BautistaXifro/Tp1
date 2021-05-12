#include "server_hill_cipher.h"
#include <math.h>
#include <ctype.h>

#define MAXKEYLENGTH 16
#define MAXMSGLENGTH 256

static void hill_numeric_maping(char* string, int* array);

void hill_init(hill_cipher_t* self, char* key) {
    if (!self) {
        printf("Error. No se aceptan parametros nulos.\n");
        return;
    }

    memset(self->key, 0, sizeof(self->key));
    strncpy(self->key, key, sizeof(self->key));
}

void hill_filter_message(char* msg){
    int j = 0;
    const int maxLongString = strlen(msg);
    char filter_msg[MAXMSGLENGTH];

    for (int i = 0; i < maxLongString; i++){
        if (isupper(msg[i])){
            filter_msg[j] = msg[i];
            j++;
        }
    }
    filter_msg[j] = '\0';
    memset(msg,0,strlen(msg));
    snprintf(msg, maxLongString, "%s", filter_msg);
}

int hill_calculate_dimension(hill_cipher_t* self, unsigned char* msg){
    int dimension = (int) sqrt(strlen(self->key));
    int excess, long_cipher_array;
    if ((excess = strlen((char *) msg) % dimension)!= 0){
        long_cipher_array = strlen((char *) msg) + (dimension - excess);
    }else{
        long_cipher_array = strlen((char *) msg);
    }

    return long_cipher_array;
}

//devuelve la longitud del vector numerico
void hill_cipher(hill_cipher_t* self, unsigned char* msg, int* cipher_msg){
    if (!msg){
        printf("Error!! el mensaje es nulo\n");
        return;
    }

    int aux = 0;
    int dimension = (int) sqrt(strlen(self->key));
    int key_array[MAXKEYLENGTH];
    int msg_numeric_array[MAXMSGLENGTH];


    //mapeo el mensaje y la key a un array numerico siguiendo a0z25
    hill_numeric_maping((char *)msg, msg_numeric_array);
    hill_numeric_maping(self->key, key_array);

    
    while (aux < strlen((char *) msg)){
        int position = 0;
        for (int i = 0; i < dimension; i++){
            int suma = 0;
            for (int j = 0; j < dimension; j++){
                if (j + aux >= strlen((char *)msg)){
                    suma += key_array[position] * 0;
                }else{
                    suma += key_array[position] * msg_numeric_array[j + aux];
                }
                position++;
            }
            cipher_msg[i + aux] = (suma) % 26;
        }
        aux += dimension;
    }
}

static void hill_numeric_maping(char* string, int* array){
    for (int i = 0; i < strlen(string); i++){
        int numeber_char = string[i];
        array[i] = numeber_char - 65;
    }
}

void hill_destroy(hill_cipher_t* self) {
    if (!self) {
        return;
    }
    memset(self->key, 0, sizeof(self->key));
}
