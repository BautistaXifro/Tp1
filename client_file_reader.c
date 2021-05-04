#include "client_file_reader.h"
#include <string.h>

#define FILE_MODE "r"

int file_reader_init(file_reader_t* self, char* file_name) {
    if (self == NULL) return -1;
    
    if (strcmp (file_name,"-") == 0) {
        self->file = stdin;
        return 0;
    }
    
    if ((self->file = fopen(file_name, FILE_MODE)) == NULL)return -1;
    return 0;
}

int file_reader_read(file_reader_t* self, char* buf, unsigned int bufLength) {
    if (!self) {
        return -1;
    }

    char* return_value = fgets(buf, bufLength, self->file);

    while (strcmp(buf, "\n") == 0 && return_value == NULL){
        return_value = fgets(buf, bufLength, self->file);
    }

    if (return_value == NULL){
        return 1;
    }

    return 0;
}

void file_reader_destroy(file_reader_t* self) {
  if (self->file != stdin) {
    fclose(self->file);
  }

  return;
}
