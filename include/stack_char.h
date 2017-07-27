#ifndef STACK_CHAR_H_
#define STACK_CHAR_H_
#include <stdlib.h>
#include "bool.h"

typedef struct {
	size_t capacity;
	size_t size;
	unsigned char* arrp;
} stack_char;


stack_char* stack_char_create(void);

bool stack_char_push(stack_char* self, unsigned char value);

unsigned char stack_char_top(const stack_char* self);

unsigned char stack_char_pop(stack_char* self);

size_t stack_char_size(const stack_char* self);

void stack_char_clear(stack_char* self);

void stack_char_destroy(stack_char* self);

#endif
