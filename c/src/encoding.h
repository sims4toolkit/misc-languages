#pragma once

#include <stdlib.h>

#include "helpers.h";

#pragma region Reading

static uint64_t _read_uint_le(char **bufferptr, int bytes) {
  int i;
  uint64_t value = 0;
  for (i = 0; i < bytes; ++i) value += (*bufferptr)[i] * ipow(2, i);
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
  ++*bufferptr;
  return c;
}

char *read_chars(char **bufferptr, int length) {
  char str[length];
  for (int i = 0; i < length; ++i) str[i] = *bufferptr[i];
  *bufferptr += length;
  return str;
}

#pragma endregion Reading

#pragma region Writing
// TODO:
#pragma endregion Writing
