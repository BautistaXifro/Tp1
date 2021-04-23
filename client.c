#include "hill_cipher.h"
#include <ctype.h>


void filter_message(char* msg){
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


int main(int argc, char** argv){
    char msg[20];
    //cipher_msg = (int*) malloc(100 * sizeof(int));
    hill_cipher_t hill;
    printf("ingrese un text: ");
    if(scanf("%s",msg) != 1){
        printf("Error al leer el mensaje\n");
    }
    
    hill_init(&hill, "CDIB");

    filter_message(msg);

    printf("%s\n", msg);

    printf("%s\n", hill.key);

    hill_cipher(&hill,msg, cipher_msg);

    for(int i = 0; i < strlen(msg) + 1; i++){
        printf("%i", cipher_msg[i]);
    }

    printf("%s\n", msg);

    hill_destroy(&hill);

    return 0;
}