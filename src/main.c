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

    interpret();

    return EXIT_SUCCESS;
}