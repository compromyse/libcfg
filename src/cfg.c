#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 50

char* format_string(char* string) {
  char* formatted = "address: %%s";
  return formatted;
}

bool parse(const char* filename, char* keywords[]) {
  char buffer[64];
  char value[32];

  FILE* file = fopen(filename, "r");
  if (file == NULL)
    goto error;

  if (fgets(buffer, MAX_LINE_LENGTH, file) == NULL)
    goto error;

  if(fscanf(file, "%s", value) == EOF)
    printf("NOT WORKING\n");
    goto error;

  printf("%s\n", value);

  return true;

error:
  fclose(file);
  return false;
}
