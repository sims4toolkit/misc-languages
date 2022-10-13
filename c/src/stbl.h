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
  struct StringEntry *entries;
};

#pragma endregion Structs

#pragma region Functions

/**
 * @brief Prints the given string table to the console.
 *
 * @param stbl String table to print
 */
void print_stbl(struct StringTable stbl) {
  for (int i = 0; i < stbl.num_entries; ++i) {
    struct StringEntry entry = stbl.entries[i];
    printf("0x%08X: %s", entry.key, entry.value);
  }
}

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

  *bufferptr += 6;  // mnReserved + mnStringLength

  for (int i = 0; i < stbl.num_entries; ++i) {
    struct StringEntry entry;
    entry.key = read_uint32_le(bufferptr);
    if (read_char(bufferptr))  // mnFlags
      exit_with_error("Expected entry flags to be 0.");
    int length = read_uint16_le(bufferptr);
    char str[length + 1];
    entry.value = str;
    strncpy(str, buffer, length);
    str[length] = '\0';
    *bufferptr += length;
    entries[i] = entry;
  }

  return stbl;
}

#pragma endregion Functions
