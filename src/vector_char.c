#include "vector_char.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#ifndef _VOWELS_SIZE_MAX_DEF
#define _VOWELS_SIZE_MAX_DEF
#define VOWELS_SIZE_MAX (~(size_t)0)
#endif

vector_char* vector_char_create(void) {
	vector_char* self = malloc(sizeof(vector_char));
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

unsigned char vector_char_at(const vector_char* self, size_t index) {
	assert (index < self->size);
	return self->arrp[index];
}


bool vector_char_expand(vector_char* self, size_t expansion) {
	if (self->size + expansion > self->capacity) {
		if (self->capacity < VOWELS_SIZE_MAX / 2) {
			self->capacity *= 2;
		}
		else if (self->capacity == VOWELS_SIZE_MAX) {
			return false;
		}
		else {
			self->capacity = VOWELS_SIZE_MAX;
		}
		self->arrp = realloc(self->arrp, self->capacity);
		if (self->arrp == NULL) {
			return false;
		}
	}
	self->size += expansion;
	return true;
}

void vector_char_set(vector_char* self, size_t index, unsigned char value) {
	assert (index < self->size);
	self->arrp[index] = value;
}

bool vector_char_push_back(vector_char* self, unsigned char value) {
	if (!vector_char_expand(self, 1)) return false;
	self->arrp[self->size - 1] = value;
	return true;
}

unsigned char vector_char_pop_back(vector_char* self) {
	assert (self->size > 0);
	return self->arrp[--(self->size)];
}

size_t vector_char_size(const vector_char* self) {
	return self->size;
}

void vector_char_clear(vector_char* self) {
	self->size = 0;
}

void vector_char_destroy(vector_char* self) {
	free(self->arrp);
	free(self);
}
