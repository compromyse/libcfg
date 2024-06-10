#include <stdio.h>

#include "../include/cfg.h"

char* keywords[] = { "address", "port" };

int main() {
  char** results = parse("test.cfg", keywords);

  for (int i = 0; results[i] != NULL; i++) {
    printf("%s: %s\n", keywords[i], results[i]);
  }

  return 0;
}
