#include <stdio.h>

#include "../include/cfg.h"

CfgVariable* variables[] = {
  &(CfgVariable) {
    "address",
    STRING
  },
  &(CfgVariable) {
    "port",
    INTEGER
  }
};

int main() {
  void** results = parse("test.cfg", variables);

  printf("%s: %s\n", variables[0]->name, (char*)results[0]);
  printf("%s: %d\n", variables[1]->name, *(int*)results[1]);

  return 0;
}
