#include "vm.h"

static stack_char *stack_a, *stack_e;
static unsigned char register_i, register_o, register_u, eof_register, overflow_register, underflow_register;

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

    while (programCounter < bytecode->size) {
        switch (bytecode->arrp[programCounter++]) {
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

    /* following lines used for debugging purposes only */
    /*
    size_t i;
    for (i = 0; i < bytecode->size - 1; i++) {
        printf("%u, ", bytecode->arrp[i]);
    }
    printf("%u\n", bytecode->arrp[i]);
    */


    vector_char_destroy(bytecode);
    stack_char_destroy(stack_a);
    stack_char_destroy(stack_e);
}

void handleADD() {
    stack_char* destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break;

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        interpret_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination) + stack_char_pop(destination);
    overflow_register = (result > UCHAR_MAX) ? result - UCHAR_MAX : 0;
    stack_char_push(destination, result & UCHAR_MAX);
}

void handleSUBTRACT() {
    stack_char* destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break;

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        interpret_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination);
    result = stack_char_pop(destination) - result;
    underflow_register = (result < 0) ? -result : 0;
    stack_char_push(destination, result & UCHAR_MAX);
}

void handleAND() {
    stack_char* destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break;

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        interpret_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination) & stack_char_pop(destination);
    stack_char_push(destination, result);
}

void handleOR() {
    stack_char* destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break;

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        interpret_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination) | stack_char_pop(destination);
    stack_char_push(destination, result);
}

void handleNOT() {
    stack_char* destination;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break;

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 1)
        interpret_error("destination stack needs to be at least 1 element tall.");

    stack_char_push(destination, !(stack_char_pop(destination)));
}

void handleXOR() {
    stack_char* destination;
    int result;

    /* only possible next values are stacks a and e */
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            destination = stack_a;
            break;

        case STACK_E:
            destination = stack_e;
            break;
    }
    if (destination->size < 2)
        interpret_error("destination stack needs to be at least 2 elements tall.");

    result = stack_char_pop(destination) ^ stack_char_pop(destination);
    stack_char_push(destination, result);
}

void handleREAD() {
    int c;
    if ((c = getchar()) == EOF) {
        eof_register = 1;
        c = 0;
    }
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!stack_char_push(stack_a, c))
                interpret_error("stack a too large, program out of memory!");
            break;
        case STACK_E:
            if (!stack_char_push(stack_e, c))
                interpret_error("stack e too large, program out of memory!");
            break;
        case REGISTER_I:
            register_i = c;
            break;
        case REGISTER_O:
            register_o = c;
            break;
        case REGISTER_U:
            register_u = c;
            break;
    }
}

void handleCWRITE() {
    int c;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            c = stack_char_pop(stack_a);
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            c = stack_char_pop(stack_e);
            break;
        case REGISTER_I:
            c = register_i;
            break;
        case REGISTER_O:
            c = register_o;
            break;
        case REGISTER_U:
            c = register_u;
            break;
        case NUMBER:
            c = bytecode->arrp[programCounter++];
            break;
    }
    putchar(c);
}

void handleSWRITE() {
    size_t startOfString;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!stack_char_push(stack_a, 0))
                interpret_error("stack a too large, program out of memory!");
            startOfString = stack_a->size - 1;
            while (startOfString && stack_a->arrp[--startOfString]);
            fputs((char*)(stack_a->arrp + startOfString), stdout);
            stack_a->size = startOfString; /* pops of the just-printed string */
            break;
        case STACK_E:
            if (!stack_char_push(stack_e, 0))
                interpret_error("stack e too large, program out of memory!");
            startOfString = stack_e->size - 1;
            while (startOfString && stack_e->arrp[--startOfString]);
            fputs((char*)(stack_e->arrp + startOfString), stdout);
            stack_e->size = startOfString; /* pops of the just-printed string */
            break;
        case NUMBER:
            while (bytecode->arrp[programCounter]) {
                putchar(bytecode->arrp[programCounter]);
                programCounter++;
            }
            programCounter++;
            break;
    }
}

void handleNWRITE() {
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            printf("%d", stack_char_pop(stack_a));
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            printf("%d", stack_char_pop(stack_e));
            break;
        case REGISTER_I:
            printf("%d", register_i);
            break;
        case REGISTER_O:
            printf("%d", register_o);
            break;
        case REGISTER_U:
            printf("%d", register_u);
            break;
        case STACK_A_SIZE:
            printf("%d", (stack_a->size < UCHAR_MAX) ? (int)stack_a->size : UCHAR_MAX);
            break;
        case STACK_E_SIZE:
            printf("%d", (stack_e->size < UCHAR_MAX) ? (int)stack_e->size : UCHAR_MAX);
            break;
        case OVERFLOW:
            printf("%d", overflow_register);
            break;
        case UNDERFLOW:
            printf("%d", underflow_register);
            break;
        case IO_EOF:
            printf("%d", eof_register);
            break;
        case NUMBER:
            printf("%d", bytecode->arrp[programCounter++]);
            break;
    }
}

void handleCOPY() {
    int data;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            data = stack_char_top(stack_a);
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            data = stack_char_top(stack_e);
            break;
        case REGISTER_I:
            data = register_i;
            break;
        case REGISTER_O:
            data = register_o;
            break;
        case REGISTER_U:
            data = register_u;
            break;
        case STACK_A_SIZE:
            data = (stack_a->size < UCHAR_MAX) ? stack_a->size : UCHAR_MAX;
            break;
        case STACK_E_SIZE:
            data = (stack_e->size < UCHAR_MAX) ? stack_e->size : UCHAR_MAX;
            break;
        case OVERFLOW:
            data = overflow_register;
            break;
        case UNDERFLOW:
            data = underflow_register;
            break;
        case IO_EOF:
            data = eof_register;
            break;
        case NUMBER:
            data = bytecode->arrp[programCounter++];
            break;
    }
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!stack_char_push(stack_a, data))
                interpret_error("stack a too large, program out of memory!");
            break;
        case STACK_E:
            if (!stack_char_push(stack_e, data))
                interpret_error("stack e too large, program out of memory!");
            break;
        case REGISTER_I:
            register_i = data;
            break;
        case REGISTER_O:
            register_o = data;
            break;
        case REGISTER_U:
            register_u = data;
            break;
    }
}

void handlePOP() {
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            stack_char_pop(stack_a);
            break;

        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            stack_char_pop(stack_e);
            break;
    }
}

void handleDUP() {
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            if (!stack_char_push(stack_a, stack_char_top(stack_a)))
                interpret_error("stack a too large, program out of memory!");
            break;

        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            if (!stack_char_push(stack_e, stack_char_top(stack_e)))
                interpret_error("stack e too large, program out of memory!");
            break;
    }
}

void handleSWAP() {
    int temp;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (stack_a->size < 2)
                interpret_error("stack a needs at least 2 elements!");
            temp = stack_a->arrp[stack_a->size - 2];
            stack_a->arrp[stack_a->size - 2] = stack_a->arrp[stack_a->size - 1];
            stack_a->arrp[stack_a->size - 1] = temp;
            break;

        case STACK_E:
            if (stack_e->size < 2)
                interpret_error("stack e needs at least 2 elements!");
            temp = stack_e->arrp[stack_e->size - 2];
            stack_e->arrp[stack_e->size - 2] = stack_e->arrp[stack_e->size - 1];
            stack_e->arrp[stack_e->size - 1] = temp;
            break;
    }
}

void handleROTATE() {
    int temp;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (stack_a->size < 3)
                interpret_error("stack a needs at least 3 elements!");
            temp = stack_a->arrp[stack_a->size - 3];
            stack_a->arrp[stack_a->size - 3] = stack_a->arrp[stack_a->size - 2];
            stack_a->arrp[stack_a->size - 2] = stack_a->arrp[stack_a->size - 1];
            stack_a->arrp[stack_a->size - 1] = temp;
            break;

        case STACK_E:
            if (stack_e->size < 3)
                interpret_error("stack e needs at least 3 elements!");
            temp = stack_e->arrp[stack_e->size - 3];
            stack_e->arrp[stack_e->size - 3] = stack_e->arrp[stack_e->size - 2];
            stack_e->arrp[stack_e->size - 2] = stack_e->arrp[stack_e->size - 1];
            stack_e->arrp[stack_e->size - 1] = temp;
            break;
    }
}

/* completed to here */

void handleJEQ() {
    int source;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            source = stack_char_top(stack_a);
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            source = stack_char_top(stack_e);
            break;
        case REGISTER_I:
            source = register_i;
            break;
        case REGISTER_O:
            source = register_o;
            break;
        case REGISTER_U:
            source = register_u;
            break;
        case STACK_A_SIZE:
            source = (stack_a->size < UCHAR_MAX) ? stack_a->size : UCHAR_MAX;
            break;
        case STACK_E_SIZE:
            source = (stack_e->size < UCHAR_MAX) ? stack_e->size : UCHAR_MAX;
            break;
        case OVERFLOW:
            source = overflow_register;
            break;
        case UNDERFLOW:
            source = underflow_register;
            break;
        case IO_EOF:
            source = eof_register;
            break;
    }
    /* condition met */
    if (!source) {
        programCounter += sizeof(size_t);
    }
    else {
        memcpy(&programCounter, bytecode->arrp + programCounter, sizeof(size_t));
    }
}

void handleJNEQ() {
    int source;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            source = stack_char_top(stack_a);
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            source = stack_char_top(stack_e);
            break;
        case REGISTER_I:
            source = register_i;
            break;
        case REGISTER_O:
            source = register_o;
            break;
        case REGISTER_U:
            source = register_u;
            break;
        case STACK_A_SIZE:
            source = (stack_a->size < UCHAR_MAX) ? stack_a->size : UCHAR_MAX;
            break;
        case STACK_E_SIZE:
            source = (stack_e->size < UCHAR_MAX) ? stack_e->size : UCHAR_MAX;
            break;
        case OVERFLOW:
            source = overflow_register;
            break;
        case UNDERFLOW:
            source = underflow_register;
            break;
        case IO_EOF:
            source = eof_register;
            break;
    }
    /* condition met */
    if (source) {
        programCounter += sizeof(size_t);
    }
    else {
        memcpy(&programCounter, bytecode->arrp + programCounter, sizeof(size_t));
    }
}

void handleJPOS() {
    int source;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            source = stack_char_top(stack_a);
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            source = stack_char_top(stack_e);
            break;
        case REGISTER_I:
            source = register_i;
            break;
        case REGISTER_O:
            source = register_o;
            break;
        case REGISTER_U:
            source = register_u;
            break;
        case STACK_A_SIZE:
            source = (stack_a->size < UCHAR_MAX) ? stack_a->size : UCHAR_MAX;
            break;
        case STACK_E_SIZE:
            source = (stack_e->size < UCHAR_MAX) ? stack_e->size : UCHAR_MAX;
            break;
        case OVERFLOW:
            source = overflow_register;
            break;
        case UNDERFLOW:
            source = underflow_register;
            break;
        case IO_EOF:
            source = eof_register;
            break;
    }
    /* condition met */
    if (!(source & 1 << 7) && source) {
        programCounter += sizeof(size_t);
    }
    else {
        memcpy(&programCounter, bytecode->arrp + programCounter, sizeof(size_t));
    }
}

void handleJNEG() {
    int source;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            source = stack_char_top(stack_a);
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            source = stack_char_top(stack_e);
            break;
        case REGISTER_I:
            source = register_i;
            break;
        case REGISTER_O:
            source = register_o;
            break;
        case REGISTER_U:
            source = register_u;
            break;
        case STACK_A_SIZE:
            source = (stack_a->size < UCHAR_MAX) ? stack_a->size : UCHAR_MAX;
            break;
        case STACK_E_SIZE:
            source = (stack_e->size < UCHAR_MAX) ? stack_e->size : UCHAR_MAX;
            break;
        case OVERFLOW:
            source = overflow_register;
            break;
        case UNDERFLOW:
            source = underflow_register;
            break;
        case IO_EOF:
            source = eof_register;
            break;
    }
    /* condition met */
    if (source & 1 << 7) {
        programCounter += sizeof(size_t);
    }
    else {
        memcpy(&programCounter, bytecode->arrp + programCounter, sizeof(size_t));
    }
}

void handleJNPOS() {
    int source;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            source = stack_char_top(stack_a);
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            source = stack_char_top(stack_e);
            break;
        case REGISTER_I:
            source = register_i;
            break;
        case REGISTER_O:
            source = register_o;
            break;
        case REGISTER_U:
            source = register_u;
            break;
        case STACK_A_SIZE:
            source = (stack_a->size < UCHAR_MAX) ? stack_a->size : UCHAR_MAX;
            break;
        case STACK_E_SIZE:
            source = (stack_e->size < UCHAR_MAX) ? stack_e->size : UCHAR_MAX;
            break;
        case OVERFLOW:
            source = overflow_register;
            break;
        case UNDERFLOW:
            source = underflow_register;
            break;
        case IO_EOF:
            source = eof_register;
            break;
    }
    /* condition met */
    if ((source & 1 << 7) || !source) {
        programCounter += sizeof(size_t);
    }
    else {
        memcpy(&programCounter, bytecode->arrp + programCounter, sizeof(size_t));
    }
}

void handleJNNEG() {
    int source;
    switch (bytecode->arrp[programCounter++]) {
        case STACK_A:
            if (!(stack_a->size))
                interpret_error("stack a is empty!");
            source = stack_char_top(stack_a);
            break;
        case STACK_E:
            if (!(stack_e->size))
                interpret_error("stack e is empty!");
            source = stack_char_top(stack_e);
            break;
        case REGISTER_I:
            source = register_i;
            break;
        case REGISTER_O:
            source = register_o;
            break;
        case REGISTER_U:
            source = register_u;
            break;
        case STACK_A_SIZE:
            source = (stack_a->size < UCHAR_MAX) ? stack_a->size : UCHAR_MAX;
            break;
        case STACK_E_SIZE:
            source = (stack_e->size < UCHAR_MAX) ? stack_e->size : UCHAR_MAX;
            break;
        case OVERFLOW:
            source = overflow_register;
            break;
        case UNDERFLOW:
            source = underflow_register;
            break;
        case IO_EOF:
            source = eof_register;
            break;
    }
    /* condition met */
    if (!(source & 1 << 7)) {
        programCounter += sizeof(size_t);
    }
    else {
        memcpy(&programCounter, bytecode->arrp + programCounter, sizeof(size_t));
    }
}

void handleJUMP() {
    memcpy(&programCounter, bytecode->arrp + programCounter, sizeof(size_t));
}
