#include "parser.h"
#include "builtin_funcs.h"
#include "string.h"
#include "stdlib.h"
#include "lexer.h"

VarEnvironment *variables;
uint64_t variables_count = 0;

Token current;

static void advance(void) {
    current = lexer_next(); 
}

static Token expect(TokensType expected, ErrorStructure error) {
    Token tok = current;

    switch (expected) {
        case TOK_TYPE:
            if (current.type == TOK_TYPE_INT || 
                current.type == TOK_TYPE_FLOAT || 
                current.type == TOK_TYPE_STRING || 
                current.type == TOK_TYPE_CHAR || 
                current.type == TOK_TYPE_BOOL) {
                
                advance();
                return tok;
            }
            raise_error(error);
            break;

        case TOK_NEWLINE:
            if (current.type == TOK_NEWLINE || 
                current.type == TOK_SEMICOLON || 
                current.type == TOK_EOF) {
                
                advance();
                return tok;
            }
            raise_error(error);
            break;

        default:
            if (current.type != expected) {
                raise_error(error);
            }
            break;
    }

    advance();

    return tok;
}

void parser_threads(void) {
    advance();
    while (true) { 
        
        if (current.type == TOK_EOF) {
            break;
        }

        if (current.type == TOK_VAR) {
            advance();

            Token varName = expect(TOK_IDENT, errorIdent);

            expect(TOK_COLON, errorColon);
            Token varType = expect(TOK_TYPE, errorType);
            expect(TOK_EQUAL, errorEqual);
            Token varValue;
            switch (varType.type) {
                case TOK_TYPE_FLOAT: varValue = expect(TOK_FLOAT, errorVarValueType); break;
            
                default: varValue = expect(TOK_INT, errorVarValueType); break;
            }
            expect(TOK_NEWLINE, errorNewline);
            
            if (variables_count >= 100) {
                raise_error(errorVarLimit);
            } else {
                variables[variables_count].name = strdup(varName.text);
                variables[variables_count].type = varType.type;
                if (variables[variables_count].type == TOK_TYPE_INT) {
                    variables[variables_count].value.int_value = varValue.number;
                }
            }

            variables_count++;
        } else {
            advance();
        }
    }
}

void parser_init(const char *src) {
    lexer_init(src);
    variables = malloc(sizeof(VarEnvironment) * 100);
    parser_threads();
    printf("1st Var: %s\n", variables[0].name);
}