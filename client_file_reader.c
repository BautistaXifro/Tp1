#include "client_file_reader.h"
#include <string.h>

#define FILE_MODE "r"

int file_reader_init(file_reader_t* self, char* file_name) {
    if (self == NULL) return -1;
    
    if (strcmp(file_name,"-") == 0) {
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

    while (fgets(buf, bufLength, self->file) != NULL){
        if (strcmp(buf, "\n") == 0){
            continue;
        }else return 0;
    }
    return 1;
}

void file_reader_destroy(file_reader_t* self) {
  if (self->file != stdin) {
    fclose(self->file);
  }

  return;
}
