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
void print_stbl(struct StringTable *stbl) {
  for (int i = 0; i < stbl->num_entries; ++i)
    printf("0x%08X: %s\n", stbl->entries[i].key, stbl->entries[i].value);
}

/**
 * @brief Reads and returns a string table from the file at the given path.
 *
 * @param filepath Path of file containing STBL data
 * @return struct StringTable String table read from specified file
 */
struct StringTable *read_stbl(const char *filepath) {
  char *buffer = malloc_buffer_from_file(filepath);
  char **bufferptr = &buffer;

  if (strncmp(buffer, "STBL", 4) != 0)  // mnFileIdentifier
    exit_with_error("Expected STBL to begin with \"STBL\".");
  *bufferptr += 4;

  if (read_uint16_le(bufferptr) != 5)  // mnVersion
    exit_with_error("Expected STBL to be version 5.");

  if (read_char(bufferptr))  // mbCompressed
    exit_with_error("Expected STBL to not be compressed.");

  struct StringTable *stbl =
      (struct StringTable *)malloc(sizeof(struct StringTable));
  stbl->num_entries = read_uint64_le(bufferptr);
  stbl->entries = (struct StringEntry *)malloc(sizeof(struct StringEntry) *
                                               stbl->num_entries);

  *bufferptr += 2;  // mnReserved can be ignored

  uint32_t total_length = read_uint32_le(bufferptr);
  char *strings_buffer = (char *)malloc(total_length);
  char **strings_bufferptr = &strings_buffer;

  for (int i = 0; i < stbl->num_entries; ++i) {
    stbl->entries[i].key = read_uint32_le(bufferptr);
    if (read_char(bufferptr))  // mnFlags
      exit_with_error("Expected entry flags to be 0.");
    size_t string_length = read_uint16_le(bufferptr);
    strncpy(*strings_bufferptr, *bufferptr, string_length);
    (*strings_bufferptr)[string_length] = '\0';
    stbl->entries[i].value = *strings_bufferptr;
    *strings_bufferptr += string_length + 1;
    *bufferptr += string_length;
  }

  return stbl;
}

#pragma endregion Functions
