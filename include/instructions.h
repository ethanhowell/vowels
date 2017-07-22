#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_
typedef enum {
	/* Data instructions */
	ADD = __LINE__,
	SUBTRACT = __LINE__,
	AND = __LINE__,
	OR = __LINE__,
	NOT = __LINE__,
	XOR = __LINE__,
	READ = __LINE__,
	CWRITE = __LINE__,
	SWRITE = __LINE__,
	NWRITE = __LINE__,
	COPY = __LINE__,
	POP = __LINE__,
	DUP = __LINE__,
	SWAP = __LINE__,
	ROTATE = __LINE__,
	JEQ = __LINE__,
	JNEQ = __LINE__,
	JPOS = __LINE__,
	JNEG = __LINE__,
	JNPOS = __LINE__,
	JNNEG = __LINE__,
	JUMP = __LINE__,

	/* Data destinations */
	STACK_A = __LINE__,
	STACK_E = __LINE__,
	REGISTER_I = __LINE__,
	REGISTER_O = __LINE__,
	REGISTER_U = __LINE__,
	STACK_A_SIZE = __LINE__,
	STACK_E_SIZE = __LINE__,
	OVERFLOW = __LINE__,
	UNDERFLOW = __LINE__,
	IO_EOF = __LINE__,
	NUMBER = __LINE__
} Instruction;

#endif