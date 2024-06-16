#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/cfg.h"

#define FORMAT_STRING_LENGTH(x, y) strlen(x) + strlen(y) + 1

static size_t size_of_null_terminated_array(CfgVariable** array) {
    size_t i = 0;
    while(array[i]) i++;
    return i;
}

static char* format(const CfgVariable* variable) {
  const char* format_specifier;

  switch (variable->type) {
    case STRING:
      format_specifier = " = %s";
      break;
    case INTEGER:
      format_specifier = " = %d";
      break;
    default:
      return NULL;
  }

  size_t new_length = FORMAT_STRING_LENGTH(variable->name, format_specifier);
  char* formatted = calloc(new_length, sizeof(char));

  strcpy(formatted, variable->name);
  strcat(formatted, format_specifier);

  return formatted;
}

static void* find(const CfgVariable* variable, FILE* file) {
  void* value = NULL;
  switch (variable->type) {
    case STRING:
      value = calloc(64, sizeof(char));
      break;
    case INTEGER:
      value = calloc(64, sizeof(int));
      break;
  }

  char* formatted_keyword = format(variable);
  if (formatted_keyword == NULL)
    return NULL;

  char* line;
  size_t len;

  fseek(file, 0L, SEEK_SET);
  while (getline(&line, &len, file) != -1)
    if (sscanf(line, formatted_keyword, value) != 0)
      return value;
    else
      line = NULL;

  return NULL;
}

void** parse(const char* filename, CfgVariable* variables[]) {
  size_t n_variables = size_of_null_terminated_array(variables);
  void** results = calloc(n_variables, sizeof(void*));

  FILE* file = fopen(filename, "r");
  if (file == NULL)
    return NULL;

  for (size_t i = 0; i < n_variables; i++)
    results[i] = find(variables[i], file);

  fclose(file);
  return results;
}
