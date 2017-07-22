#ifndef BLOCK_H_
#define BLOCK_H_
#include <stdlib.h>

typedef enum {
	WHILE,
	IF
} Blocktype;

typedef struct {
	Blocktype type;
	size_t startIndex;
} Block;

#endif
