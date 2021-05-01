#ifndef __HILL_CIPHER_H__
#define __HILL_CIPHER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
    char key[16];
}hill_cipher_t;

void hill_init(hill_cipher_t* self, char* key);

void hill_cipher(hill_cipher_t* self, unsigned char* msg, int* cipher_msg);

int hill_calculate_dimension(hill_cipher_t* self, unsigned char* msg);

void hill_filter_message(char* msg);

static void hill_numeric_maping(unsigned char* msg, int* msg_array);

void hill_char_maping(unsigned char* msg, int* msg_array, int size);

void hill_destroy(hill_cipher_t* self);

#endif