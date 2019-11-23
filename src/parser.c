#include "parser.h"

#define JUMP_ADDRESS_OFFSET 2

vector_char* bytecode = NULL;
static stack_block* blockStack = NULL;

static size_t currentLine = 1, currentChar = 0;
static int lastCharRead;

void parseError(const char* message) {
    if (bytecode) vector_char_destroy(bytecode);
    if (blockStack) stack_block_destroy(blockStack);
    fclose(currentFile);

    syntax_error(currentLine, currentChar, message);
}


void parse() {
    bytecode = vector_char_create();
    blockStack = stack_block_create();
    if (!bytecode || !blockStack) {
        parseError("out of memory -- program size too large.");
    }

    /* ignore shebang line (if it exists) */
    if ((lastCharRead = getc(currentFile)) == '#' &&
        (lastCharRead = getc(currentFile) == '!')) {
        while (getc(currentFile) != '\n');
    }
    else {
        ungetc(lastCharRead, currentFile);
    }

    while (true) {
        switch (getNextVowel()) {
            case VOWEL_A:
                parseArithmetic();
                break;

            case VOWEL_E:
                parseDataJuggling();
                break;

            case VOWEL_I:
                parseBlock();
                break;

            case VOWEL_O:
                parseEndblock();
                break;

            case VOWEL_U:
                parseIO();
                break;

            case VOWEL_Y:
            case VOWEL_EOF:
                if (stack_block_size(blockStack)) {
                    parseError ("expected end of block sequence.");
                }
                stack_block_destroy(blockStack);
                return;
        }
    }
}

void parseArithmetic() {
    switch (match(VOWEL_A | VOWEL_E | VOWEL_I | VOWEL_O | VOWEL_U | VOWEL_Y)) {
        case VOWEL_A:
            bytecodePush(ADD);
            break;

        case VOWEL_E:
            bytecodePush(SUBTRACT);
            break;

        case VOWEL_I:
            bytecodePush(AND);
            break;

        case VOWEL_O:
            bytecodePush(NOT);
            break;

        case VOWEL_U:
            bytecodePush(OR);
            break;

        case VOWEL_Y:
            bytecodePush(XOR);
            break;

        default:
            parseError("There has been an error in the parser subroutine.");
    }

    matchDestination(STACKS);
}

void parseDataJuggling() {
    switch (match(VOWEL_A | VOWEL_E | VOWEL_I | VOWEL_O | VOWEL_U)) {
        case VOWEL_A:
            bytecodePush(DUP);
            matchDestination(STACKS);
            break;
        case VOWEL_E:
            bytecodePush(COPY);
            matchDestination(STACKS | REGISTERS | NUMBERS | MAGIC_NUMS);
            matchDestination(STACKS | REGISTERS);
            break;
        case VOWEL_I:
            bytecodePush(SWAP);
            matchDestination(STACKS);
            break;
        case VOWEL_O:
            bytecodePush(POP);
            matchDestination(STACKS);
            break;
        case VOWEL_U:
            bytecodePush(ROTATE);
            matchDestination(STACKS);
            break;
        default:
            parseError("There has been an error in the parser subroutine.");
    }
}

void parseIO() {
    switch (match(VOWEL_A | VOWEL_E | VOWEL_I | VOWEL_O)) {
        case VOWEL_A:
            bytecodePush(READ);
            matchDestination(STACKS | REGISTERS);
            break;
        case VOWEL_E:
            bytecodePush(SWRITE);
            matchDestination(STACKS | STRINGS);
            break;
        case VOWEL_I:
            bytecodePush(CWRITE);
            matchDestination(STACKS | REGISTERS | NUMBERS);
            break;
        case VOWEL_O:
            bytecodePush(NWRITE);
            matchDestination(STACKS | REGISTERS | NUMBERS | MAGIC_NUMS);
            break;
        default:
            parseError("There has been an error in the parser subroutine.");
    }
}

void parseBlock() {
    Block currentBlock;
    switch (match(VOWEL_A | VOWEL_E)) {
        case VOWEL_A:
            currentBlock.type = IF;
            break;
        case VOWEL_E:
            currentBlock.type = WHILE;
            break;
        default:
            parseError("There has been an error in the parser subroutine.");
    }
    currentBlock.startIndex = bytecode->size;
    switch (match(VOWEL_A | VOWEL_E | VOWEL_I | VOWEL_O | VOWEL_U | VOWEL_Y)) {
        case VOWEL_A:
            bytecodePush(JNEQ);
            break;
        case VOWEL_E:
            bytecodePush(JEQ);
            break;
        case VOWEL_I:
            bytecodePush(JNEG);
            break;
        case VOWEL_O:
            bytecodePush(JPOS);
            break;
        case VOWEL_U:
            bytecodePush(JNPOS);
            break;
        case VOWEL_Y:
            bytecodePush(JNNEG);
            break;
        default:
            parseError("There has been an error in the parser subroutine.");
    }
    matchDestination(STACKS | REGISTERS | MAGIC_NUMS);
    if (!vector_char_expand(bytecode, sizeof(size_t)))
        parseError("out of memory -- program size too large.");
    if (!stack_block_push(blockStack, currentBlock))
        parseError("out of memory -- too many nested code blocks.");
}

void parseEndblock() {
    Block lastBlock;
    if (!stack_block_size(blockStack)) {
        parseError("unexpected end block sequence.");
    }
    lastBlock = stack_block_pop(blockStack);
    if (lastBlock.type == WHILE) {
        bytecodePush(JUMP);
        if (!vector_char_expand(bytecode, sizeof(size_t)))
            parseError("out of memory -- program size too large.");
        memcpy(bytecode->arrp + bytecode->size - sizeof(size_t), &(lastBlock.startIndex), sizeof(size_t));
    }
    memcpy(bytecode->arrp + lastBlock.startIndex + JUMP_ADDRESS_OFFSET, &(bytecode->size), sizeof(size_t));
}

int parseNum() {
    int parsedNum, i;
    parsedNum = 0, i = 0;
    while (i++ < 4) {
        switch (match(VOWEL_A | VOWEL_E | VOWEL_I | VOWEL_O | VOWEL_U)) {
            case VOWEL_E:
                parsedNum = parsedNum * 5 + 0;
                break;
            case VOWEL_A:
                parsedNum = parsedNum * 5 + 1;
                break;
            case VOWEL_O:
                parsedNum = parsedNum * 5 + 2;
                break;
            case VOWEL_I:
                parsedNum = parsedNum * 5 + 3;
                break;
            case VOWEL_U:
                parsedNum = parsedNum * 5 + 4;
                break;
            default:
                parseError("There has been an error in the parser subroutine.");
        }
    }
    bytecodePush(parsedNum &= UCHAR_MAX);
    return parsedNum;
}

void parseMagicNum() {
    switch (match(VOWEL_A | VOWEL_E | VOWEL_I | VOWEL_O | VOWEL_U)) {
        case VOWEL_A:
            bytecodePush(STACK_A_SIZE);
            break;
        case VOWEL_E:
            bytecodePush(STACK_E_SIZE);
            break;
        case VOWEL_I:
            bytecodePush(OVERFLOW);
            break;
        case VOWEL_O:
            bytecodePush(UNDERFLOW);
            break;
        case VOWEL_U:
            bytecodePush(IO_EOF);
            break;
        default:
            parseError("There has been an error in the parser subroutine.");
    }
}

Vowel getNextVowel() {
    int c;
    while ((lastCharRead = c = getc(currentFile)) != EOF) {
        currentChar++;
        switch(c) {
            case 'A':
            case 'a':
                return VOWEL_A;
            case 'E':
            case 'e':
                return VOWEL_E;
            case 'I':
            case 'i':
                return VOWEL_I;
            case 'O':
            case 'o':
                return VOWEL_O;
            case 'U':
            case 'u':
                return VOWEL_U;
            case 'Y':
            case 'y':
                return VOWEL_Y;
            case '\n':
                currentLine++;
                currentChar = 0;
        }
    }
    return VOWEL_EOF;
}

Vowel match(int flag) {
    Vowel v;
    if ((v = getNextVowel()) & flag)
        return v;
    else {
        switch (v) {
            case VOWEL_EOF:
                parseError("unexpected end-of-file.");
                break;
            case VOWEL_A:
                parseError("unexpected vowel 'A'.");
                break;
            case VOWEL_E:
                parseError("unexpected vowel 'E'.");
                break;
            case VOWEL_I:
                parseError("unexpected vowel 'I'.");
                break;
            case VOWEL_O:
                parseError("unexpected vowel 'O'.");
                break;
            case VOWEL_U:
                parseError("unexpected vowel 'U'.");
                break;
            case VOWEL_Y:
                parseError("unexpected vowel 'Y'.");
                break;
        }
        /* note: control should never return from parseError */
        return (Vowel)NULL;
    }
}

void matchDestination(int flag) {
    Vowel v;
    switch (v = getNextVowel()) {
        case VOWEL_A:
            if (!(flag & STACKS))
                parseError("unexpected stack destination argument.");
            bytecodePush(STACK_A);
            break;

        case VOWEL_E:
            if (!(flag & STACKS))
                parseError("unexpected stack destination argument.");
            bytecodePush(STACK_E);
            break;

        case VOWEL_I:
            if (!(flag & REGISTERS))
                parseError("unexpected register destination argument.");
            bytecodePush(REGISTER_I);
            break;

        case VOWEL_O:
            if (!(flag & REGISTERS))
                parseError("unexpected register destination argument.");
            bytecodePush(REGISTER_O);
            break;

        case VOWEL_U:
            if (!(flag & REGISTERS))
                parseError("unexpected register destination argument.");
            bytecodePush(REGISTER_U);
            break;

        case VOWEL_Y:
            if (getNextVowel() == VOWEL_Y) {
                if (!(flag & MAGIC_NUMS))
                    parseError("unexpected magic number destination argument.");
                parseMagicNum();
            }
            else {
                ungetc(lastCharRead, currentFile);
                bytecodePush(NUMBER);
                if (flag & NUMBERS)
                    parseNum();
                else if (flag & STRINGS)
                    while(parseNum());
                else
                    parseError("unexpected number destination argument.");
            }
            break;
        default:
            parseError("There has been an error in the parser subroutine.");
    }
}