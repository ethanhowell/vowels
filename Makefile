CC = gcc

CFLAGS = -g -ansi -Wall -Wpedantic -Wextra

DEPDIR = include
_DEPS = block.h bool.h error.h instructions.h main.h parser.h stack_block.h stack_char.h vector_char.h vm.h
DEPS = $(patsubst %,$(DEPDIR)/%,$(_DEPS))

SRCDIR = src

ODIR = obj
_OBJ = error.o main.o parser.o stack_block.o stack_char.o vector_char.o vm.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

PROG_NAME = vowels

.PHONY: clean fresh all

all: $(PROG_NAME)

$(PROG_NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(PROG_NAME)

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $< -I$(DEPDIR)
	@echo

clean:
	$(RM) $(ODIR)/*.o *~; $(RM) $(PROG_NAME)

fresh: clean all