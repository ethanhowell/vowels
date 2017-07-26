#ifndef VM_H_
#define VM_H_
#include "parser.h"
#include "stack_char.h"
#include "error.h"

void interpret_error(const char* message);
void interpret(void);

#endif