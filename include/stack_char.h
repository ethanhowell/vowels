#ifndef STACK_CHAR_H_
#define STACK_CHAR_H_

#include "vector_char.h"
#include <stdlib.h>

typedef struct {
	vector_char* vec;
} stack_char;

stack_char* stack_char_create(void);

bool stack_char_push(stack_char* self, unsigned char elem);

unsigned char stack_char_pop(stack_char* self);

unsigned char stack_char_top(const stack_char* self);

size_t stack_char_size(const stack_char* self);

void stack_char_clear(stack_char* self);

void stack_char_destroy(stack_char* self);

#endif
