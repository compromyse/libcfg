#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_OF_STRING_ARRAY(array) ({ \
    size_t i; \
    for (i = 0; array[i] != NULL; i++); \
    i; \
})

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

  char* formatted_keyword = format_string(keyword);

  char* line;
  size_t len;

  while (getline(&line, &len, file) != -1)
    if (sscanf(line, formatted_keyword, value) != EOF)
      return value;

  return NULL;
}

char** parse(const char* filename, char* keywords[]) {
  size_t n_keywords = SIZE_OF_STRING_ARRAY(keywords);
  char** results = calloc(n_keywords, sizeof(char*));

  FILE* file = fopen(filename, "r");
  if (file == NULL)
    goto error;

  for (size_t i = 0; i < n_keywords; i++) {
    results[i] = find_value(keywords[i], file);
  }

  return results;

error:
  fclose(file);
  return false;
}
