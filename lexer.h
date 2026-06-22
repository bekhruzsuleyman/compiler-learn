#pragma once

typedef enum {
    TOK_EOF,
    TOK_MODULE,
    TOK_VAR,
    TOK_FN,
    TOK_RETURN,
    
    TOK_INT,
    TOK_STRING,
    TOK_CHAR,
    TOK_FLOAT,
    TOK_BOOL,
    TOK_IDENT,
    
    TOK_LPAREN, TOK_RPAREN,
    TOK_LBRACE, TOK_RBRACE,
    TOK_COLON, TOK_SEMICOLON, TOK_COMMA,
    TOK_QUOTA,
    TOK_EQUAL,
    TOK_ARROW,
    TOK_LESS, TOK_GREATER,

    TOK_TYPE,
    TOK_TYPE_INT, TOK_TYPE_FLOAT, TOK_TYPE_STRING, TOK_TYPE_BOOL, TOK_TYPE_CHAR,

    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH,
    TOK_NEWLINE,
} TokensType;


typedef struct {
    TokensType type;
    char text[64];
    unsigned long long number;
} Token;

void lexer_init(const char *src);
Token lexer_next(void);
const char *token_name(TokensType type);
