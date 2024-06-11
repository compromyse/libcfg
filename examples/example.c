#include <stdio.h>

#include "../include/cfg.h"

CfgVariable* variables[] = {
  &(CfgVariable) {
    "port",
    INTEGER
  },
  &(CfgVariable) {
    "address",
    STRING
  }
};

int main(int argc, char** argv) {
  (void) argc;
  (void) argv;


  void** results = parse("example.cfg", variables);

  int* port = results[0];
  char* address = results[1];

  printf("address = %s\n", address);
  printf("port = %d\n", *port);

  return 0;
}
