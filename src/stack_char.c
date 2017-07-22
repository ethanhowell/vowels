#include "stack_char.h"
#include <stdlib.h>
#include "error.h"

stack_char* stack_char_create(void) {
	stack_char* self = malloc(sizeof(stack_char));
	if (self == NULL) {
		return NULL;
	}

	self->vec = vector_char_create();

	return self;
}

bool stack_char_push(stack_char* self, unsigned char elem) {
	return vector_char_push_back(self->vec, elem);
}

unsigned char stack_char_pop(stack_char* self) {
	return vector_char_pop_back(self->vec);
}

unsigned char stack_char_top(const stack_char* self) {
	return vector_char_at(self->vec, vector_char_size(self->vec) - 1);
}

size_t stack_char_size(const stack_char* self) {
	return vector_char_size(self->vec);
}

void stack_char_clear(stack_char* self) {
	vector_char_clear(self->vec);
}

void stack_char_destroy(stack_char* self) {
	vector_char_destroy(self->vec);
	free(self);
}
