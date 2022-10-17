#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encoding.h"
#include "helpers.h"

typedef struct StringEntry {
  uint32_t key;
  char* value;
} StringEntry;

typedef struct StringTable {
  size_t count;
  StringEntry* entries;
} StringTable;

/**
 * @brief Frees all memory associated with a StringTable.
 *
 * @param stbl Pointer to StringTable to free
 */
void destroy_stbl(StringTable* stbl) {
  free(stbl->entries[0].value);
  free(stbl->entries);
  free(stbl);
}

/**
 * @brief Creates a new StringTable containing the data in the specified file.
 *
 * @param filepath Path to file containing STBL data
 *
 * @return StringTable* Pointer to created StringTable
 */
StringTable* load_stbl(const char* filepath) {
  char** bufferptr = load_file_buffer(filepath);
  char* buffer = *bufferptr;

  if (strncmp(buffer, "STBL", 4) != 0)  // mnFileIdentifier
    exit_with_error("Expected STBL to begin with \"STBL\".");
  *bufferptr += 4;

  if (read_uint16_le(bufferptr) != 5)  // mnVersion
    exit_with_error("Expected STBL to be version 5.");

  if (read_char(bufferptr))  // mbCompressed
    exit_with_error("Expected STBL to not be compressed.");

  uint64_t count = read_uint64_le(bufferptr);
  *bufferptr += 2;  // mnReserved
  uint32_t strings_length = read_uint32_le(bufferptr);

  StringTable* stbl = (StringTable*)malloc(sizeof(StringTable));
  StringEntry* entries = (StringEntry*)malloc(count * sizeof(StringEntry));
  char* strings = (char*)malloc(strings_length);
  char** strings_offset = &strings;

  stbl->count = count;
  stbl->entries = entries;

  for (size_t i = 0; i < count; ++i) {
    stbl->entries[i].key = read_uint32_le(bufferptr);
    if (read_char(bufferptr))  // mnFlags
      exit_with_error("Expected entry flags to be 0.");
    size_t string_length = read_uint16_le(bufferptr);
    strncpy(*strings_offset, *bufferptr, string_length);
    (*strings_offset)[string_length] = '\0';
    stbl->entries[i].value = *strings_offset;
    *strings_offset += string_length + 1;
    *bufferptr += string_length;
  }

  free(buffer);  // FIXME:

  return stbl;
}

/**
 * @brief Prints the data in the StringTable to the console.
 *
 * @param stblptr Pointer to StringTable to print
 */
void print_stbl(StringTable* stbl) {
  for (int i = 0; i < stbl->count; ++i)
    printf("0x%08X: %s\n", stbl->entries[i].key, stbl->entries[i].value);
}
