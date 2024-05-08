#include <stdio.h>
#include <stdlib.h>

long get_size(FILE *f);

int main() {
  const int length = 3;

  FILE *f;
  f = fopen("in.txt", "r");
  if (f == NULL) {
    perror("Error opening file");
    return 1;
  }

  long size = get_size(f);

  char *value = malloc(size);
  if (value == NULL) {
    perror("Heap alloc failed");
    fclose(f);
    return 1;
  } else {
    printf("memallocsucsess");
  }

  fread(value, size, 1, f);

  // split the string into the first 100 char.

  char name[5] = "1.txt";
  for (int i = 0; i < length; i++) {

    FILE *fp = fopen(name, "w");
    if (fp == NULL) {
      perror("Error opening the file\n");
      free(value);
      fclose(f);
      return 1;
    }

    fprintf(fp, "%s", value);
    fclose(f);
    name[0]++;
    printf("created file\n");
  }
  free(value);
  fclose(f);
}

long get_size(FILE *f) {
  if (fseek(f, 0, SEEK_END) != 0) {
    perror("fseek error");
    return -1;
  }

  long size = ftell(f);

  if (fseek(f, 0, SEEK_SET) != 0) {
    perror("fseek error");
    return -1;
  }
  return size;
}
