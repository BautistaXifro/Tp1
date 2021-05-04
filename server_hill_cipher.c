#include "server_hill_cipher.h"
#include <math.h>
#include <ctype.h>

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
    char filter_msg[maxLongString];

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
    if ((excess = strlen((char *) msg) % 2)!= 0 && dimension % 2 == 0){
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
    const int keyArrayLength = strlen(self->key);
    const int msgNumericArrayLength = strlen((char *) msg);
    int dimension = (int) sqrt(strlen(self->key));
    int* key_array = (int *) malloc(keyArrayLength * sizeof(int));
    int* msg_numeric_array = (int *) malloc(msgNumericArrayLength * sizeof(int));

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
    free(key_array);
    free(msg_numeric_array);
}

static void hill_numeric_maping(char* string, int* array){
    for (int i = 0; i < strlen(string); i++){
        switch (string[i])
        {
        case 'A':
            array[i] = 0;
            break;

        case 'B':
            array[i] = 1;
            break;
        
        case 'C':
            array[i] = 2;
            break;

        case 'D':
            array[i] = 3;
            break;

        case 'E':
            array[i] = 4;
            break;

        case 'F':
            array[i] = 5;
            break;
        
        case 'G':
            array[i] = 6;
            break;
        
        case 'H':
            array[i] = 7;
            break;
        
        case 'I':
            array[i] = 8;
            break;
        
        case 'J':
            array[i] = 9;
            break;
        
        case 'K':
            array[i] = 10;
            break;
        
        case 'L':
            array[i] = 11;
            break;
        
        case 'M':
            array[i] = 12;
            break;
        
        case 'N':
            array[i] = 13;
            break;
        
        case 'O':
            array[i] = 14;
            break;
        
        case 'P':
            array[i] = 15;
            break;
        
        case 'Q':
            array[i] = 16;
            break;
        
        case 'R':
            array[i] = 17;
            break;
        
        case 'S':
            array[i] = 18;
            break;
        
        case 'T':
            array[i] = 19;
            break;
        
        case 'U':
            array[i] = 20;
            break;
        
        case 'V':
            array[i] = 21;
            break;
        
        case 'W':
            array[i] = 22;
            break;
        
        case 'X':
            array[i] = 23;
            break;
        
        case 'Y':
            array[i] = 24;
            break;

        case 'Z':
            array[i] = 25;
            break;

        default:
            printf("Error no es un char\n"); 
            break;
        }
    }
}

void hill_destroy(hill_cipher_t* self) {
    if (!self) {
        return;
    }
    memset(self->key, 0, sizeof(self->key));
}
