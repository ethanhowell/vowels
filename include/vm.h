#ifndef VM_H_
#define VM_H_
#include <limits.h>
#include <stdio.h>
#include "parser.h"
#include "stack_char.h"
#include "error.h"

void interpret_error(const char* message);
void interpret(void);

void handleADD(void);
void handleSUBTRACT(void);
void handleAND(void);
void handleOR(void);
void handleNOT(void);
void handleXOR(void);

void handleREAD(void);
void handleCWRITE(void);
void handleSWRITE(void);
void handleNWRITE(void);

void handleCOPY(void);
void handlePOP(void);
void handleDUP(void);
void handleSWAP(void);
void handleROTATE(void);

void handleJEQ(void);
void handleJNEQ(void);
void handleJPOS(void);
void handleJNEG(void);
void handleJNPOS(void);
void handleJNNEG(void);
void handleJUMP(void);

#endif