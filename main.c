#include <stdio.h>
#include "parser.h"

int main(void) {
    const char *code =
        "let newVar: int = 12\n"
        "\n";
    
    lexer_init(code);

    while (1) {
        Token token = lexer_next();

        printf("%s", token_name(token.type));

        if (token.type == TOK_IDENT) {
            printf("(%s)", token.text);
        }

        if (token.type == TOK_INT) {
            printf("(%llu)", token.number);
        }

        printf("\n");

        if (token.type == TOK_EOF) break;
    }

    parser_init(code);

    return 0;
}