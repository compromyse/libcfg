#include <stdbool.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 50

bool parse(const char* filename) {
  char buffer[50];
  FILE* file = fopen(filename, "r");

  if (file == NULL) return false;

  // if (fgets(buffer, MAX_LINE_LENGTH, file) == NULL) return false;

  if(fscanf(file, "address: %s", buffer) == EOF) printf("NOT WORKING\n");

  printf("%s\n", buffer);

  fclose(file);
  return true;
}
