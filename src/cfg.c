#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/cfg.h"

#define SIZE_OF_NULL_TERMINATED_ARRAY(array) ({ \
    size_t i; \
    for (i = 0; array[i] != NULL; i++); \
    i; \
})

#define FORMAT_STRING_LENGTH(string1, string2) ({ \
  strlen(string) + strlen(string) + 1; \
})

static char* format(char* string, char* type_format_specifier) {
  size_t new_length = FORMAT_STRING_LENGTH(string, type_format_specifier);
  char* formatted = calloc(new_length, sizeof(char));

  strcpy(formatted, string);
  strcat(formatted, type_format_specifier);

  return formatted;
}

static char* find_string(CfgVariable* variable, FILE* file) {
  char* value = calloc(50, sizeof(char));
  if (value == NULL)
    return NULL;

  char* formatted_keyword = format(variable->name, ": %s");

  char* line;
  size_t len;

  while (getline(&line, &len, file) != -1)
    if (sscanf(line, formatted_keyword, value) != EOF)
      return value;

  return NULL;
}

static int* find_integer(CfgVariable* variable, FILE* file) {
  int* value = calloc(50, sizeof(int));
  if (value == NULL)
    return NULL;

  char* formatted_keyword = format(variable->name, ": %d");

  char* line;
  size_t len;

  while (getline(&line, &len, file) != -1)
    if (sscanf(line, formatted_keyword, value) != EOF)
      return value;

  return NULL;
}

void** parse(const char* filename, CfgVariable* variables[]) {
  size_t n_keywords = SIZE_OF_NULL_TERMINATED_ARRAY(variables);
  void** results = calloc(n_keywords, sizeof(char*));

  FILE* file = fopen(filename, "r");
  if (file == NULL)
    goto error;

  for (size_t i = 0; i < n_keywords; i++)
    switch (variables[i]->type) {
      case STRING:
        results[i] = find_string(variables[i], file);
        break;
      case INTEGER:
        results[i] = find_integer(variables[i], file);
        break;
    }

  return results;

error:
  fclose(file);
  return NULL;
}
