#ifndef VECTOR_CHAR_H_
#define VECTOR_CHAR_H_
#include <stdlib.h>
#include "bool.h"

#define DEFAULT_INITIAL_CAPACITY 10

typedef struct {
	size_t capacity;
	size_t size;
	unsigned char* arrp;
} vector_char;

/**
  * Returns a pointer to the created vector_char.
  * Note: the pointer must be destroyed via the vector_char_destroy() function.
  *
  * @error if there is no more memory
  * @return a pointer to the created object
  */
vector_char* vector_char_create(void);

unsigned char vector_char_at(const vector_char* self, size_t index);

void vector_char_set(vector_char* self, size_t index, unsigned char value);

bool vector_char_expand(vector_char* self, size_t expansion);

bool vector_char_push_back(vector_char* self, unsigned char value);

unsigned char vector_char_pop_back(vector_char* self);

size_t vector_char_size(const vector_char* self);

void vector_char_clear(vector_char* self);

void vector_char_destroy(vector_char* self);

#endif
