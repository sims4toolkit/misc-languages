#pragma once

#include <stdlib.h>

#include "helpers.h"

#pragma region Reading

static uint64_t _read_uint_le(char **bufferptr, int bytes) {
  uint32_t byte;  // FIXME: this can probably be a char, but it's not working
  uint64_t value = 0;

  for (int i = 0; i < bytes; ++i) {
    byte = (*bufferptr)[i] & (uint32_t)0xFF;
    uint64_t factor = i ? (((uint64_t)1) << (i * 8)) : 1;
    value += byte * factor;
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
  ++*bufferptr;
  return c;
}

#pragma endregion Reading

#pragma region Writing
// TODO:
#pragma endregion Writing
