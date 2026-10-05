CC ?= cc
# strdup is POSIX, not ISO C11: without this define it is implicitly
# declared as returning int, and the program crashes on 64-bit systems.
CFLAGS ?= -std=c11 -D_POSIX_C_SOURCE=200809L -Wall

SRC := main.c lexer.c parser.c builtin_funcs.c

compiler-learn: $(SRC) lexer.h parser.h builtin_funcs.h
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -f compiler-learn

.PHONY: clean
