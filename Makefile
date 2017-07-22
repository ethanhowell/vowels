CC = gcc

CFLAGS = -g -Wall -ansi -Wextra

DEPDIR = include
_DEPS = block.h bool.h error.h instructions.h main.h parser.h stack_block.h stack_char.h vector_char.h
DEPS = $(patsubst %,$(DEPDIR)/%,$(_DEPS))

SRCDIR = src

ODIR = obj
_OBJ = error.o main.o parser.o stack_block.o stack_char.o vector_char.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: clean fresh all

all: vowels

vowels: $(OBJ)
	$(CC) $(CFLAGS) $^ -o vowels

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $< -I$(DEPDIR)
	@echo

clean:
	$(RM) $(ODIR)/*.o *~; $(RM) vowels

fresh: clean all