#ifndef PARSER_H_
#define PARSER_H_
#include <limits.h>
#include <string.h>
#include "main.h"
#include "bool.h"
#include "vector_char.h"
#include "stack_block.h"
#include "error.h"
#include "instructions.h"

extern vector_char* bytecode;

typedef enum {
	VOWEL_EOF = 1,
	VOWEL_A = 1 << 1,
	VOWEL_E = 1 << 2,
	VOWEL_I = 1 << 3,
	VOWEL_O = 1 << 4,
	VOWEL_U = 1 << 5,
	VOWEL_Y = 1 << 6
} Vowel;

typedef enum {
	STACKS = 1,
	REGISTERS = 1 << 2,
	NUMBERS = 1 << 3,
	STRINGS = 1 << 4,
	MAGIC_NUMS = 1 << 5
} Destination;

void parseFile(FILE* file);
void parseString(char* string);

void parse();

int getCharacter();
void ungetCharacter(int c);

void parseError(const char* message);

void parseArithmetic(void);
void parseDataJuggling(void);
void parseIO(void);

void parseBlock(void);
void parseEndblock(void);

int parseNum(void);
void parseMagicNum(void);

Vowel getNextVowel(void);

Vowel match(int flag);
void matchDestination(int flag);

#define bytecodePush(instr) \
			if (!vector_char_push_back(bytecode, instr)) \
				parseError("out of memory -- program size too large.");


#endif