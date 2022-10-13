#include <stdio.h>
#include <string.h>

void read_stbl(const char *filepath) {
  printf("Reading STBL: %s", filepath);
  // FILE *file = fopen(filepath, "r");
  // fclose(file);
}

void read_pkg(const char *filepath) {
  printf("Reading PKG: %s", filepath);
  // FILE *file = fopen(filepath, "r");
  // fclose(file);
}

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
