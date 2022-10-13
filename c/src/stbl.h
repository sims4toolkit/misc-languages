#pragma once

#include <stdio.h>
#include <string.h>

#include "encoding.h"
#include "helpers.h"

#pragma region Structs

struct StringEntry {
  uint32_t key;
  char *value;
};

struct StringTable {
  uint64_t num_entries;
  uint32_t string_length;
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
  char *buffer = get_buffer(filepath);
  char **bufferptr = &buffer;

  if (strncmp(buffer, "STBL", 4) != 0)  // mnFileIdentifier
    exit_with_error("Expected STBL to begin with \"STBL\".");
  *bufferptr += 4;

  if (read_uint16_le(bufferptr) != 5)  // mnVersion
    exit_with_error("Expected STBL to be version 5.");

  if (read_char(bufferptr))  // mbCompressed
    exit_with_error("Expected STBL to not be compressed.");

  struct StringTable stbl;
  stbl.num_entries = read_uint64_le(bufferptr);
  struct StringEntry entries[stbl.num_entries];
  stbl.entries = entries;

  *bufferptr += 2;  // mnReserved

  stbl.string_length = read_uint32_le(bufferptr);

  for (int i = 0; i < stbl.num_entries; ++i) {
    struct StringEntry entry;
    entry.key = read_uint32_le(bufferptr);
    entry.value = read_string(bufferptr);
    entries[i] = entry;
  }

  return stbl;
}

#pragma endregion Functions
