#ifndef MAIN_H_
#define MAIN_H_

#define VOWELS_VERSION_NUMBER "0.9"
#define INPUT_FILE_SIZE 256
#define TRUE 1
#define FALSE 0

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

void interruptHandler(int flag);

#endif