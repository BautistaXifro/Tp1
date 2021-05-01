#include "hill_cipher.h"
#include <math.h>
#include <ctype.h>

void hill_init(hill_cipher_t* self, char* key) {
    if (!self) {
        printf("Error. No se aceptan parametros nulos.\n");
    }

    memset(self->key, 0, sizeof(self->key));
    strncpy(self->key, key, sizeof(self->key));
}

void hill_filter_message(char* msg){
    int i,j;
    int max_long_string = strlen(msg);
    char filter_msg[max_long_string];
    i = j = 0;

    for(i; i < max_long_string; i++){
        if(isupper(msg[i])){
            filter_msg[j] = msg[i];
            j++;
        }
    }
    filter_msg[j] = '\0';   
    memset(msg,0,sizeof(msg));
    strncpy(msg, filter_msg, strlen(filter_msg));
}

int hill_calculate_dimension(hill_cipher_t* self, unsigned char* msg){
    int dimension = (int) sqrt(strlen(self->key));
    int excess, long_cipher_array;
    if((excess = strlen(msg) % 2)!= 0 && dimension % 2 == 0){
        long_cipher_array = strlen(msg) + (dimension - excess);
    }else{
        long_cipher_array = strlen(msg);
    }

    return long_cipher_array;
}

//devuelve la longitud del vector numerico
void hill_cipher(hill_cipher_t* self, unsigned char* msg, int* cipher_msg){
    if(!msg){
        printf("Error!! el mensaje es nulo\n");
        return;
    }

    int aux = 0;
    int dimension = (int) sqrt(strlen(self->key));
    int key_array[strlen(self->key)];
    int msg_numeric_array[strlen(msg)];

    //mapeo el mensaje y la key a un array numerico siguiendo a0z25
    hill_numeric_maping(msg, msg_numeric_array);
    hill_numeric_maping(self->key, key_array);

    
    while(aux < strlen(msg)){
        int position = 0;
        for(int i = 0; i < dimension; i++){
            int suma = 0;
            for(int j = 0; j < dimension; j++){
                if(j + aux >= strlen(msg)){
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

static void hill_numeric_maping(unsigned char* string, int* array){
    for(int i = 0; i < strlen(string); i++){
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

void hill_char_maping(unsigned char* string, int* array, int size){
    for(int i = 0; i < size; i++){
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

void hill_destroy(hill_cipher_t* self) {
    if (!self) {
        return;
    }
    memset(self->key, 0, sizeof(self->key));
}