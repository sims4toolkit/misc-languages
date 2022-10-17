#pragma once

#include <stdio.h>

/**
 * @brief Terminates the program with an error message.
 *
 * @param msg Message to print to console
 */
void exit_with_error(const char *msg) {
  printf("%s\n", msg);
  exit(1);
}

/**
 * @brief Loads a file into a buffer.
 *
 * @param filepath Full path to file to load
 */
char **load_file_buffer(const char *filepath) {
  FILE *fileptr;
  char **bufferptr;
  long filelen;

  fileptr = fopen(filepath, "rb");
  fseek(fileptr, 0, SEEK_END);
  filelen = ftell(fileptr);
  rewind(fileptr);
  *bufferptr = (char *)malloc(filelen * sizeof(char));
  fread(*bufferptr, filelen, 1, fileptr);
  fclose(fileptr);

  return bufferptr;
}
