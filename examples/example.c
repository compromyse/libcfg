#include <stdio.h>

#include "../include/cfg.h"

char* keywords[] = { "address" };

int main() {
  parse("test.cfg", keywords);
  return 0;
}
