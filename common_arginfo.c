#include "common_arginfo.h"
#include <stdio.h>
#include <string.h>

void arginfo_init(arginfo_t* self, int argc, char* argv[]){
    if(self == NULL || argv == NULL) return;

    memset(self->port, 0, sizeof(self->port));
    memset(self->key, 0, sizeof(self->key));
    
    strncpy(self->port, argv[1], sizeof(self->port));
    strncpy(self->key, argv[2], sizeof(self->key));
}


void arginfo_destroy(arginfo_t* self){
    if(self == NULL) return;

    memset(self->port, 0, sizeof(self->port));
    memset(self->key, 0, sizeof(self->key));
}