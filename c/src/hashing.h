#pragma once

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

uint32_t fnv32(const char* string) {
  uint32_t hash = 0x811C9DC5u;
  size_t chars = strlen(string);
  for (size_t i = 0; i < chars; ++i) {
    hash *= 0x01000193u;
    hash ^= (uint32_t)tolower(string[i]);
  }
  return hash;
}

uint64_t fnv64(const char* string) {
  uint64_t hash = 0xCBF29CE484222325ul;
  size_t chars = strlen(string);
  for (size_t i = 0; i < chars; ++i) {
    hash *= 0x00000100000001B3ull;
    hash ^= (uint64_t)tolower(string[i]);
  }
  return hash;
}
