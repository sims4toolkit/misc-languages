#pragma once

#include <stdio.h>
#include <string.h>

#include "helpers.h"

#pragma region Structs

struct StringEntry {
  uint32_t key;
  char *value;
};

struct StringTable {
  struct StringEntry *entries;
};

#pragma endregion Structs

#pragma region Functions

/**
 * @brief Reads and returns a string table from the file at the given path.
 *
 * @param filepath Path of file containing STBL data
 * @return struct StringTable String table read from specified file
 */
struct StringTable read_stbl(const char *filepath) {
  char *buffer;
  struct StringTable stbl;

  buffer = get_buffer(filepath);

  if (strncmp(buffer, "STBL", 4) != 0) {
    exit_with_error("Expected STBL to begin with \"STBL\".");
  }

  printf("Working on it...");  // TODO:

  return stbl;
}

#pragma endregion Functions
