#ifndef COMMON_ARGINFO_H_
#define COMMON_ARGINFO_H_

#define KEY_LENGTH 16
#define SERVICE_NAME_LENGTH 10

typedef struct{
    char key[KEY_LENGTH];
    char port[SERVICE_NAME_LENGTH];
}arginfo_t;


void arginfo_init(arginfo_t* self, int argc, char* argv[]);


void arginfo_destroy(arginfo_t* self);

#endif