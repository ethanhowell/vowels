#ifndef STACK_BLOCK_H_
#define STACK_BLOCK_H_
#include <stdlib.h>
#include "block.h"
#include "bool.h"


typedef struct {
	size_t capacity;
	size_t size;
	Block* arrp;
} stack_block;


stack_block* stack_block_create(void);

bool stack_block_push(stack_block* self, Block value);

Block stack_block_top(const stack_block* self);

Block stack_block_pop(stack_block* self);

size_t stack_block_size(const stack_block* self);

void stack_block_clear(stack_block* self);

void stack_block_destroy(stack_block* self);

#endif
