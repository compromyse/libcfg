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

#define FORMAT_STRING_LENGTH(string1, string2) ({ strlen(string1) + strlen(string2) + 1; })

static char* format(CfgVariable* variable) {
  const char* format_specifier;

  switch (variable->type) {
    case STRING:
      format_specifier = " = %s";
      break;
    case INTEGER:
      format_specifier = " = %d";
      break;
  }

  size_t new_length = FORMAT_STRING_LENGTH(variable->name, format_specifier);
  char* formatted = calloc(new_length, sizeof(char));

  strcpy(formatted, variable->name);
  strcat(formatted, format_specifier);

  return formatted;
}

static void* find(CfgVariable* variable, FILE* file) {
  void* value;
  switch (variable->type) {
    case STRING:
      value = calloc(64, sizeof(char));
      break;
    case INTEGER:
      value = calloc(64, sizeof(int));
      break;
  }
  if (value == NULL)
    return NULL;

  char* formatted_keyword = format(variable);

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
    results[i] = find(variables[i], file);

  return results;

error:
  fclose(file);
  return NULL;
}
