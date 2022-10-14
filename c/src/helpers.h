#pragma once

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Outputs a message to the console and exits with code 1.
 *
 * @param msg Message to write to console
 */
void exit_with_error(const char *msg) {
  printf("%s\n", msg);
  exit(1);
}

/**
 * @brief Allocates a buffer for the given file and returns its address.
 *
 * @param filepath Full path to file to read
 * @return char* Address to a buffer containing the file's bytes
 */
char *malloc_buffer_from_file(const char *filepath) {
  FILE *fileptr = fopen(filepath, "rb");
  fseek(fileptr, 0, SEEK_END);
  long filelen = ftell(fileptr);
  rewind(fileptr);
  char *buffer = (char *)malloc(filelen * sizeof(char));
  fread(buffer, filelen, 1, fileptr);
  fclose(fileptr);
  return buffer;
}
