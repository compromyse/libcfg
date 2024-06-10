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
  char* address = results[0];
  int* port = results[1];

  printf("address = %s\n", address);
  printf("port = %d\n", *port);

  return 0;
}
