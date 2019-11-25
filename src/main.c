#include "main.h"

FILE* currentFile = NULL;

int main(int argc, char const *argv[]) {
    int usingStdin = false;
    FILE* currentFile;
    /* install interrupt handler to flush stdout on ctrl+c */
    signal(SIGINT, interruptHandler);

    if (argc < 2) {
        currentFile = stdin;
        usingStdin = true;
    }

    else if (argc == 2 && (!strcmp("--version", argv[1]) || !strcmp("-v", argv[1]))) {
        puts("Vowels Interpreter (vowels) version " VOWELS_VERSION_NUMBER " " __DATE__);
        puts("Copyright (C) Ethan J. Howell.");
        puts("This is free software (see license in source). There is NO warranty; \nnot even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.");
        putchar('\n');
        return EXIT_SUCCESS;
    }

    else {
        if (!(currentFile = fopen(argv[1], "r"))) {
            printf("Error reading file %s. Does the file exist? Please try again.\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    parseFile(currentFile);
    
    if (!usingStdin) fclose(currentFile);
    currentFile = NULL;

    interpret();

    return EXIT_SUCCESS;
}

void interruptHandler(int flag) {
    switch (flag) {
        case SIGINT:
            fflush(stdout);
            exit(EXIT_SUCCESS);
            break;
    }
}