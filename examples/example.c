#include <stdio.h>

#include "../include/cfg.h"

CfgVariable* variables[] = {
  &(CfgVariable) {
    "address",
    STRING
  },
  &(CfgVariable) {
    "port",
    STRING
  }
};

int main() {
  char** results = parse("test.cfg", variables);

  for (int i = 0; results[i] != NULL; i++) {
    printf("%s: %s\n", variables[i]->name, results[i]);
  }

  return 0;
}
