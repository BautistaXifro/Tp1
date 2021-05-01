#include "common_file_reader.h"
#include <string.h>

#define FILE_MODE "r"

int file_reader_init(file_reader_t* self, char* file_name) {
    if(self == NULL) return -1;
    
    if (strcmp (file_name,"-") == 0) {
        self->file = stdin;
        return 0;
    }
    
    self->file = fopen(file_name, FILE_MODE);
    return 0;

}

int file_reader_read(file_reader_t* self, unsigned char* buf, unsigned int bufLength) {
    if (!self) {
        return -1;
    }

    int bytes_read = fread(buf, 1, bufLength, self->file);
    return bytes_read;
}

int file_reader_eof(file_reader_t* self) { 
    return feof(self->file);
}

void file_reader_destroy(file_reader_t* self) {
  if (self->file != stdin) {
    fclose(self->file);
  }

  return;
}