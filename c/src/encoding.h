#pragma once

#include <stdlib.h>

#include "helpers.h";

#pragma region Reading Little Endian

static uint64_t _read_uint_le(char *buffer, long int offset, int bytes) {
  int i;
  uint64_t value = 0;
  for (i = 0; i < bytes; ++i) value += buffer[i] * ipow(2, i);
  return value;
}

uint16_t read_uint16_le(char *buffer, long int offset) {
  return (uint16_t)_read_uint_le(buffer, offset, sizeof(uint16_t));
}

uint32_t read_uint32_le(char *buffer, long int offset) {
  return (uint32_t)_read_uint_le(buffer, offset, sizeof(uint32_t));
}

uint64_t read_uint64_le(char *buffer, long int offset) {
  return _read_uint_le(buffer, offset, sizeof(uint64_t));
}

#pragma endregion Reading Little Endian

#pragma region Writing Little Endian
// TODO:
#pragma endregion Writing Little Endian
