# compiler-learn

An early learning project in C: a hand-written lexer, a small parser for variable declarations, and a few built-in error helpers. It was written to understand how a language front end turns source text into tokens and then into something structured.

## What it handles

**Lexer** (`lexer.c`) turns source text into tokens:

- Keywords: `let`, `function`, `return`, `module`
- Type names: `int`, `float`, `string`, `char`, `boolean`
- Identifiers (letters, digits, `_`; up to 63 characters)
- Unsigned integer literals
- Symbols: `( ) { } : ; , = + - * / < > ->` and `"`
- Newlines are emitted as tokens; spaces, tabs and `\r` are skipped

**Parser** (`parser.c`) recognises one statement form, a typed variable declaration:

```
let name: int = 12
```

A declaration ends with a newline, `;` or end of input. Parsed variables go into a fixed table of 100 entries; only `int` values are stored. Every other token is skipped. Float and string literals are not lexed yet, so `float` declarations fail with a type error.

**Errors** (`builtin_funcs.c`) are reported as `[Kind]: message` on stderr and stop the program, for example `[SyntaxError]: Missing Colon!`.

## Build and run

Requires a C11 compiler and `make`.

```sh
make
./compiler-learn
```

The input program is hard-coded in `main.c` (`let newVar: int = 12`). The program prints the token stream, then parses the same source and prints the first variable it stored:

```
VAR
IDENT(newVar)
COLON
TYPE_INT
EQUAL
INT(12)
NEWLINE
NEWLINE
EOF
1st Var: newVar
```

`make clean` removes the binary.

The build prints two harmless compiler warnings (an unused helper in `lexer.c` and an enum comparison in `parser.c`). The Makefile defines `_POSIX_C_SOURCE` because the parser uses `strdup`, which is POSIX rather than ISO C11. Without it, `cc -std=c11` compiles the program but it crashes when run.

## See also

[flang-lite](https://github.com/bekhruzsuleyman/flang-lite) is the later, maintained language that grew out of experiments like this one.

## License

MIT. See [LICENSE](LICENSE).
