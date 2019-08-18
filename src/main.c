#include "main.h"

#define VOWELS_VERSION_NUMBER "0.9"

FILE* currentFile = NULL;

int main(int argc, char const *argv[]) {
    /* install interrupt handler to flush stdout on ctrl+c */
    signal(SIGINT, interruptHandler);

    if (argc < 2) {
       fputs("No input files. Quitting now.\n", stderr);
       exit(EXIT_FAILURE);
    }

    else if (argc == 2 && (!strcmp("--version", argv[1]) || !strcmp("-v", argv[1]))) {
        puts("Vowels Interpreter (vowels) version " VOWELS_VERSION_NUMBER " " __DATE__);
        puts("Copyright (C) Ethan J. Howell.");
        puts("This is free software (see license in source). There is NO warranty; \nnot even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.");
        putchar('\n');
        return EXIT_SUCCESS;
    }

    currentFile = fopen(argv[1], "r");
    if (!currentFile) {
        fprintf(stderr, "File %s does not exist. Quitting now.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    parse();
    fclose(currentFile);
    currentFile = NULL;

    interpret();

    return EXIT_SUCCESS;
}

void interruptHandler(int flag) {
    fflush(stdout);
    exit(EXIT_SUCCESS);
}