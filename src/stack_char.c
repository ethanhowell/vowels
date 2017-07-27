#include "stack_char.h"
#include <stdlib.h>
#include <assert.h>

#ifndef _SIZE_MAX_DEF
#define _SIZE_MAX_DEF
#define SIZE_MAX (~(size_t)0)
#endif


#define DEFAULT_INITIAL_CAPACITY 10

stack_char* stack_char_create(void) {
	stack_char* self = malloc(sizeof(stack_char));
	if (self == NULL) {
		return NULL;
	}

	self->capacity = DEFAULT_INITIAL_CAPACITY;

	self->arrp = malloc(self->capacity * sizeof(unsigned char));
	if (self->arrp == NULL) {
		return NULL;
	}

	self->size = 0;

	return self;
}

bool stack_char_push(stack_char* self, unsigned char value) {
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

unsigned char stack_char_top(const stack_char* self) {
	assert (self->size > 0);
	return self->arrp[self->size];
}

unsigned char stack_char_pop(stack_char* self) {
	assert (self->size > 0);
	return self->arrp[--(self->size)];
}

size_t stack_char_size(const stack_char* self) {
	return self->size;
}

void stack_char_clear(stack_char* self) {
	self->size = 0;
}

void stack_char_destroy(stack_char* self) {
	free(self->arrp);
	free(self);
}
