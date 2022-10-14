#pragma once

#include <stdio.h>
#include <stdlib.h>

void exit_with_error(const char *msg) {
  printf("%s\n", msg);
  exit(1);
}

void realloc_buffer_from_file(char **bufferptr, const char *filepath) {
  FILE *fileptr = fopen(filepath, "rb");
  fseek(fileptr, 0, SEEK_END);
  long filelen = ftell(fileptr);
  rewind(fileptr);
  *bufferptr = (char *)realloc(*bufferptr, filelen * sizeof(char));
  fread(*bufferptr, filelen, 1, fileptr);
  fclose(fileptr);
}
