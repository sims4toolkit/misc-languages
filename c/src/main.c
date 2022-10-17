#include <stdio.h>
#include <string.h>

#include "stbl.h"

int main(int argc, const char **argv) {
  const char *filetype = argv[1];
  const char *filepath = argv[2];

  if (strncmp(filetype, "stbl", 4) == 0) {
    StringTable *stbl = load_stbl(filepath);
    print_stbl(stbl);
    destroy_stbl(stbl);
  } else if (strncmp(filetype, "pkg", 3) == 0) {
    exit_with_error("PKG parsing not implemented.");
  } else {
    printf("Filetype not recognized: %s", filetype);
    return 1;
  }

  return 0;
}
