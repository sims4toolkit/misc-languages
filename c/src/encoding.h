#pragma once

#include <stdlib.h>
#include <string.h>

#include "helpers.h"

#pragma region Reading

static uint64_t _read_uint_le(char **bufferptr, int bytes) {
  uint64_t byte;
  uint64_t value = 0;

  for (int i = 0; i < bytes; ++i) {
    byte = (*bufferptr)[i] & 0xFFul;
    if (i) byte *= 1ul << (i * 8);
    value += byte;
  }

  *bufferptr += bytes;
  return value;
}

uint16_t read_uint16_le(char **bufferptr) {
  return (uint16_t)_read_uint_le(bufferptr, sizeof(uint16_t));
}

uint32_t read_uint32_le(char **bufferptr) {
  return (uint32_t)_read_uint_le(bufferptr, sizeof(uint32_t));
}

uint64_t read_uint64_le(char **bufferptr) {
  return _read_uint_le(bufferptr, sizeof(uint64_t));
}

char read_char(char **bufferptr) {
  char c = **bufferptr;
  *bufferptr += sizeof(char);
  return c;
}

// void read_string(char **bufferptr, char *dst, size_t bytes) {
//   strncpy(dst, *bufferptr, bytes);
//   dst[bytes] = '\0';
//   *bufferptr += bytes;
// }

#pragma endregion Reading

#pragma region Writing
// TODO:
#pragma endregion Writing
