#ifndef __CFG_H
#define __CFG_H

#include <stdbool.h>

typedef enum {
  STRING,
  INTEGER
} VariableType;

typedef struct {
  char* name;
  VariableType type;
} CfgVariable;

char** parse(const char* filename, CfgVariable* variables[]);

#endif
