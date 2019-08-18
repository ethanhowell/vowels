#include "main.h"

#define VOWELS_VERSION_NUMBER "0.9"

FILE* currentFile = NULL;

void openInputFile(void) {
    char inputFile[256] = {0};
    puts("Please enter the name of the input file: ");

    /* Reads in input file to inputFile string then tries to open a file with that name*/
    while (!fgets(inputFile, sizeof(inputFile), stdin) || !(currentFile = fopen(strtok(inputFile, "\n"), "r"))) {
        printf("Error reading filename %s. Does the file exist? Please try again.\n", inputFile);
        puts("Please enter the name of the input file. Note - file name must be less than 255 characters: ");
    }
    return;
}

int main(int argc, char const *argv[]) {
    /* install interrupt handler to flush stdout on ctrl+c */
    signal(SIGINT, interruptHandler);

    if (argc < 2) {
        openInputFile();
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
            printf("File %s does not exist. Please try again.\n", argv[1]);
            openInputFile();
        }
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