#include "error.h"

void syntax_error(size_t line, size_t character, const char* message) {
	fprintf(stderr, "Syntax error, line %lu, character %lu: %s\n", (unsigned long)line, (unsigned long)character, message);
	exit(EXIT_FAILURE);
}