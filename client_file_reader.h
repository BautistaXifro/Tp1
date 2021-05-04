#ifndef __CLIENT_FILE_READER_H__
#define __CLIENT_FILE_READER_H__
#include <stdio.h>

typedef struct file_reader {
  FILE* file;
} file_reader_t;

int file_reader_init(file_reader_t* self, char* file_name);

int file_reader_read(file_reader_t* self, char* buf, unsigned int bufLength);

void file_reader_destroy(file_reader_t* self);


#endif