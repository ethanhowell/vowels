#include "main.h"

FILE* currentFile = NULL;

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        fputs("No input files. Quitting now.\n", stderr);
        exit(EXIT_FAILURE);
    }

    currentFile = fopen(argv[1], "r");
    if (!currentFile) {
        fprintf(stderr, "File %s does not exist. Quitting now.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    parse();
    fclose(currentFile);
    currentFile = NULL;

    /* TODO: execute code found in the bytecode vector */
    size_t i;
    for (i = 0; i < bytecode->size - 1; i++) {
        printf("%u, ", bytecode->arrp[i]);
    }
    printf("%u\n", bytecode->arrp[i]);

    vector_char_destroy(bytecode);

    return EXIT_SUCCESS;
}