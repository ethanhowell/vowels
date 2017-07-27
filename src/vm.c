#include "vm.h"

static stack_char *stack_a, *stack_e;
static unsigned char register_i, register_o, register_u, stack_a_size, stack_e_size, eof_register, overflow_register, underflow_register;

static size_t programCounter;

void interpret_error(const char* message) {
    if (stack_a) stack_char_destroy(stack_a);
    if (stack_e) stack_char_destroy(stack_e);
    vector_char_destroy(bytecode);
    runtime_error(message);
}

void interpret() {
    stack_a = stack_char_create();
    stack_e = stack_char_create();
    if (!stack_a || !stack_e) {
        interpret_error("Out of memory!");
    }

    while (programCounter++ < bytecode->size) {
        switch (bytecode->arrp[programCounter]) {
            case ADD:
                handleADD();
                break;

            case SUBTRACT:
                handleSUBTRACT();
                break;

            case AND:
                handleAND();
                break;

            case OR:
                handleOR();
                break;

            case NOT:
                handleNOT();
                break;

            case XOR:
                handleXOR();
                break;

            case READ:
                handleREAD();
                break;

            case CWRITE:
                handleCWRITE();
                break;

            case SWRITE:
                handleSWRITE();
                break;

            case NWRITE:
                handleNWRITE();
                break;

            case COPY:
                handleCOPY();
                break;

            case POP:
                handlePOP();
                break;

            case DUP:
                handleDUP();
                break;

            case SWAP:
                handleSWAP();
                break;

            case ROTATE:
                handleROTATE();
                break;

            case JEQ:
                handleJEQ();
                break;

            case JNEQ:
                handleJNEQ();
                break;

            case JPOS:
                handleJPOS();
                break;

            case JNEG:
                handleJNEG();
                break;

            case JNPOS:
                handleJNPOS();
                break;

            case JNNEG:
                handleJNNEG();
                break;

            case JUMP:
                handleJUMP();
                break;

        }
    }

    size_t i;
    for (i = 0; i < bytecode->size - 1; i++) {
        printf("%u, ", bytecode->arrp[i]);
    }
    printf("%u\n", bytecode->arrp[i]);


    vector_char_destroy(bytecode);
    stack_char_destroy(stack_a);
    stack_char_destroy(stack_e);
}

void handleADD() {
    stack_char* const destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        runtime_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination) + stack_char_pop(destination);
    overflow_register = (result > UCHAR_MAX) ? result - UCHAR_MAX : 0;
    stack_char_push(destination, result & UCHAR_MAX);
}

void handleSUBTRACT() {
    stack_char* const destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        runtime_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination);
    result = stack_char_pop(destination) - result;
    underflow_register = (result < 0) ? -result : 0;
    stack_char_push(destination, result & UCHAR_MAX);
}

void handleAND() {
    stack_char* const destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        runtime_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination) & stack_char_pop(destination);
    stack_char_push(destination, result);
}

void handleOR() {
    stack_char* const destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        runtime_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination) | stack_char_pop(destination);
    stack_char_push(destination, result);
}

void handleNOT() {
    stack_char* const destination;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 1)
        runtime_error("destination stack needs to be at least 1 element tall.");

    stack_char_push(destination, !(stack_char_pop(destination)));
}

void handleXOR() {
    stack_char* const destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        runtime_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination) ^ stack_char_pop(destination);
    stack_char_push(destination, result);
}

/* completed to here */

void handleREAD() {

}

void handleCWRITE() {

}

void handleSWRITE() {

}

void handleNWRITE() {

}

void handleCOPY() {

}

void handlePOP() {

}

void handleDUP() {

}

void handleSWAP() {

}

void handleROTATE() {

}

void handleJEQ() {

}

void handleJNEQ() {

}

void handleJPOS() {

}

void handleJNEG() {

}

void handleJNPOS() {

}

void handleJNNEG() {

}

void handleJUMP() {

}
