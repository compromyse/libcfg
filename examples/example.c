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
  },
  NULL
};

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [config.cfg]\n", argv[0]);
    return 1;
  }

  void** results = parse(argv[1], variables);

  char* address = results[0];
  int* port = results[1];

  printf("address = %s\n", address);
  printf("port = %d\n", *port);

  return 0;
}
