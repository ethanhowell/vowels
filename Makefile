CC = gcc

CBASEFLAGS = -ansi
CDEBUGFLAGS = -g -Wall -Wpedantic -Wextra
CPRODFLAGS = -O2 -s

DEPDIR = include
_DEPS = block.h bool.h error.h instructions.h main.h parser.h stack_block.h stack_char.h vector_char.h vm.h
DEPS = $(patsubst %,$(DEPDIR)/%,$(_DEPS))

SRCDIR = src

ODIR = obj
_OBJ = error.o main.o parser.o stack_block.o stack_char.o vector_char.o vm.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

PROG_NAME = vowels

.PHONY: clean fresh all debug web

all: CFLAGS = $(CBASEFLAGS) $(CPRODFLAGS)
all: $(PROG_NAME)

debug: CFLAGS = $(CBASEFLAGS) $(CDEBUGFLAGS)
debug: $(PROG_NAME)

web: CC = emcc
web: PROG_NAME = docs/vowels.js
web: ODIR = docs/obj
web: OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
web: all

$(PROG_NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(PROG_NAME)

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS) $(ODIR)
	$(CC) -c $(CFLAGS) -o $@ $< -I$(DEPDIR)
	@echo

$(ODIR):
	mkdir $@

clean:
	$(RM) -r $(ODIR); $(RM) $(PROG_NAME)

fresh: clean all