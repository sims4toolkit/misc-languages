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
    printf("0x%08X: %s\n", entry.key, entry.value);
  }
}

/**
 * @brief Reads and returns a string table from the file at the given path.
 *
 * @param filepath Path of file containing STBL data
 * @return struct StringTable String table read from specified file
 */
struct StringTable read_stbl(const char *filepath) {
  char *buffer = malloc_buffer_from_file(filepath);
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

  uint32_t total_length = read_uint32_le(bufferptr);
  char *strings_buffer = (char *)malloc(total_length);
  char **strings_bufferptr = &strings_buffer;

  for (int i = 0; i < stbl.num_entries; ++i) {
    struct StringEntry entry;
    entry.key = read_uint32_le(bufferptr);
    if (read_char(bufferptr))  // mnFlags
      exit_with_error("Expected entry flags to be 0.");
    int length = read_uint16_le(bufferptr);
    read_string(bufferptr, *strings_bufferptr, length);
    (*strings_bufferptr)[length] = '\0';
    *strings_bufferptr += length + 1;
    entry.value = *strings_bufferptr;
    entries[i] = entry;
  }

  return stbl;
}

#pragma endregion Functions
