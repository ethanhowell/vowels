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

    switch (bytecode->arrp[programCounter++]) {
        /* TODO: handle various instructions here */
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