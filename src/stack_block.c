#include "stack_block.h"
#include <stdlib.h>
#include <assert.h>

#ifndef _SIZE_MAX_DEF
#define _SIZE_MAX_DEF
#define SIZE_MAX (~(size_t)0)
#endif


#define DEFAULT_INITIAL_CAPACITY 10

stack_block* stack_block_create(void) {
	stack_block* self = malloc(sizeof(stack_block));
	if (self == NULL) {
		return NULL;
	}

	self->capacity = DEFAULT_INITIAL_CAPACITY;

	self->arrp = malloc(self->capacity * sizeof(Block));
	if (self->arrp == NULL) {
		return NULL;
	}

	self->size = 0;

	return self;
}

bool stack_block_push(stack_block* self, Block value) {
	if (self->size >= self->capacity) {
		if (self->capacity < SIZE_MAX / 2) {
			self->capacity *= 2;
		}
		else if (self->capacity == SIZE_MAX) {
			return false;
		}
		else {
			self->capacity = SIZE_MAX;
		}
		self->arrp = realloc(self->arrp, self->capacity);
		if (self->arrp == NULL) {
			return false;
		}
	}
	self->arrp[self->size++] = value;
	return true;
}

Block stack_block_top(const stack_block* self) {
	assert (self->size > 0);
	return self->arrp[self->size];
}

Block stack_block_pop(stack_block* self) {
	assert (self->size > 0);
	return self->arrp[--(self->size)];
}

size_t stack_block_size(const stack_block* self) {
	return self->size;
}

void stack_block_clear(stack_block* self) {
	self->size = 0;
}

void stack_block_destroy(stack_block* self) {
	free(self->arrp);
	free(self);
}
