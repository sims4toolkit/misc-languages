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
 * @brief Integer exponents (https://stackoverflow.com/questions/101439).
 *
 * @param base Base to raise
 * @param exp Value to raise by
 * @return int Resulting of raising base to exp
 */
int ipow(int base, int exp) {
  int result = 1;

  for (;;) {
    if (exp & 1) result *= base;
    exp >>= 1;
    if (!exp) break;
    base *= base;
  }

  return result;
}

/**
 * @brief Copies the bytes in the file at the given path to a buffer.
 *
 * @param filepath Path to file to read
 * @return char* Buffer containing file bytes
 */
char *get_buffer(const char *filepath) {
  FILE *fileptr;
  char *buffer;
  long filelen;

  fileptr = fopen(filepath, "rb");
  fseek(fileptr, 0, SEEK_END);
  filelen = ftell(fileptr);
  rewind(fileptr);
  buffer = (char *)malloc(filelen * sizeof(char));
  fread(buffer, filelen, 1, fileptr);
  fclose(fileptr);

  return buffer;
}
