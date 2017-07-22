#ifndef ERROR_H_
#define ERROR_H_
#include <stdlib.h>
#include <stdio.h>

void syntax_error(size_t line, size_t character, const char* message);

#endif