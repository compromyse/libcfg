#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char* format_string(char* string) {
  size_t new_length = strlen(string) + strlen(": %s") + 1;
  char* formatted = calloc(new_length, sizeof(char));

  strcpy(formatted, string);
  strcat(formatted, ": %s");

  return formatted;
}

static char* find_value(char* keyword, FILE* file) {
  char* value = calloc(50, sizeof(char));
  if (value == NULL)
    return NULL;

  fseek(file, 0L, SEEK_SET);
  if(fscanf(file, format_string(keyword), value) == EOF)
    return NULL;
  
  return value;
}

bool parse(const char* filename, char* keywords[]) {
  FILE* file = fopen(filename, "r");
  if (file == NULL)
    goto error;

  printf("%s\n", find_value(keywords[0], file));

  return true;

error:
  printf("Errored\n");
  fclose(file);
  return false;
}
