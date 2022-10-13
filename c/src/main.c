#include <stdio.h>
#include <string.h>

#include "pkg.h"
#include "stbl.h"

int main(int argc, const char **argv) {
  const char *filetype = argv[1];
  const char *filepath = argv[2];

  if (strncmp(filetype, "stbl", 4) == 0) {
    read_stbl(filepath);
  } else if (strncmp(filetype, "pkg", 3) == 0) {
    read_pkg(filepath);
  } else {
    printf("Filetype not recognized: %s", filetype);
    return 1;
  }

  return 0;
}
