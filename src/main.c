#include "main.h"

FILE* currentFile = NULL;

int main(int argc, char const *argv[]) {
    if (argc < 2) {
       fputs("No input files. Quitting now.\n", stderr);
       exit(EXIT_FAILURE);
    }

    else if (argc == 2 && (!strcmp("--version", argv[1]) || !strcmp("-v", argv[1]))) {
        puts("Vowels Interpreter (vowels) version 0.9 20170728");
        puts("Copyright (C) 2017 Ethan J. Howell.");
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