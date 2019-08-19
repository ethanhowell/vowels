#ifndef MAIN_H_
#define MAIN_H_

#ifndef STR
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "bool.h"
#include "vector_char.h"
#include "parser.h"
#include "vm.h"

extern FILE* currentFile;

/* sets currentFile to the open file */
void openInputFile(void);

void interruptHandler(int flag);

#endif