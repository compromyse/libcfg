#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/cfg.h"

int format_string_length(const char* string1, const char* string2) {
  return strlen(string1) + strlen(string2) + 1;
}

size_t size_of_null_terminated_array(CfgVariable** array) {
    size_t i;
    for (i = 0; array[i] != NULL; i++);
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
  }

  size_t new_length = format_string_length(variable->name, format_specifier);
  char* formatted = calloc(new_length, sizeof(char));

  strcpy(formatted, variable->name);
  strcat(formatted, format_specifier);

  return formatted;
}

static void* find(const CfgVariable* variable, FILE* file) {
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
  size_t n_variables = size_of_null_terminated_array(variables);
  void** results = calloc(n_variables, sizeof(void*));

  FILE* file = fopen(filename, "r");
  if (file == NULL)
    return NULL;

  for (size_t i = 0; i < n_variables; i++)
    results[i] = find(variables[i], file);

  return results;

error:
  fclose(file);
  return NULL;
}
