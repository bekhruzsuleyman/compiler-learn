#include "lexer.h"
#include <ctype.h>
#include <string.h>

static const char *src;
static int pos;

void lexer_init(const char *source) {
    src = source;
    pos = 0;
}

static char peek(void) {
    return src[pos];
}

static char peek_next(void) {
    return src[pos + 1];
}

static char advance(void) {
    return src[pos++];
}

const char *token_name(TokensType type) {
    switch (type) {
        case TOK_EOF:       return "EOF";
        case TOK_MODULE:    return "MODULE";
        case TOK_TYPE_INT:      return "TYPE_INT";
        case TOK_TYPE_FLOAT:      return "TYPE_FLOAT";
        case TOK_TYPE_STRING:      return "TYPE_STRONG";
        case TOK_TYPE_CHAR:      return "TYPE_CHAR";
        case TOK_TYPE_BOOL:      return "TYPE_BOOL";
        case TOK_VAR:       return "VAR";
        case TOK_FN:        return "FUNCTION";
        case TOK_RETURN:    return "RETURN";
        case TOK_INT:       return "INT";
        case TOK_FLOAT:     return "FLOAT";
        case TOK_CHAR:      return "CHAR";
        case TOK_STRING:    return "STRING";
        case TOK_BOOL:      return "BOOL";
        case TOK_IDENT:     return "IDENT";
        case TOK_LPAREN:    return "LPAREN";
        case TOK_RPAREN:    return "RPAREN";
        case TOK_QUOTA:     return "QUOTA";
        case TOK_LBRACE:    return "LBRACE";
        case TOK_RBRACE:    return "RBRACE";
        case TOK_COLON:     return "COLON";
        case TOK_SEMICOLON: return "SEMICOLON";
        case TOK_COMMA:     return "COMMA";
        case TOK_EQUAL:     return "EQUAL";
        case TOK_LESS:      return "LESS";
        case TOK_GREATER:   return "GREATER";
        case TOK_ARROW:     return "ARROW";
        case TOK_PLUS:      return "PLUS";
        case TOK_MINUS:     return "MINUS";
        case TOK_STAR:      return "STAR";
        case TOK_SLASH:     return "SLASH";
        case TOK_NEWLINE:   return "NEWLINE";
        default:            return "UNKNOWN";
    }
}

Token lexer_next(void) {
    while (peek() == ' ' || peek() == '\t' || peek() == '\r') {
        advance();
    }

    Token token = {0};

    if (peek() == '\0') {
        token.type = TOK_EOF;
        return token;
    }

    if (peek() == '\n') {
        advance();
        token.type = TOK_NEWLINE;
        return token;
    }

    if (isalpha(peek()) || peek() == '_') {
        int i = 0;

        while (isalnum(peek()) || peek() == '_') {
            if (i < 63) token.text[i++] = advance();
            else advance();
        }

        token.text[i] = '\0';

        if (strcmp(token.text, "module") == 0) token.type = TOK_MODULE;
        else if (strcmp(token.text, "int") == 0) token.type = TOK_TYPE_INT;
        else if (strcmp(token.text, "float") == 0) token.type = TOK_TYPE_FLOAT;
        else if (strcmp(token.text, "string") == 0) token.type = TOK_TYPE_STRING;
        else if (strcmp(token.text, "char") == 0) token.type = TOK_TYPE_CHAR;
        else if (strcmp(token.text, "boolean") == 0) token.type = TOK_TYPE_BOOL;
        else if (strcmp(token.text, "function") == 0) token.type = TOK_FN;
        else if (strcmp(token.text, "let") == 0) token.type = TOK_VAR;
        else if (strcmp(token.text, "return") == 0) token.type = TOK_RETURN;
        else token.type = TOK_IDENT;

        return token;
    }

    if (isdigit(peek())) {
        unsigned long long value = 0;
    
        while (isdigit(peek())) {
            value = value * 10 + (advance() - '0');
        }
    
        token.type = TOK_INT;
        token.number = value;
        return token;
    }

    char c = advance();

    switch (c) {
        case '(': token.type = TOK_LPAREN; break;
        case ')': token.type = TOK_RPAREN; break;
        case '{': token.type = TOK_LBRACE; break;
        case '}': token.type = TOK_RBRACE; break;
        case '\"':token.type = TOK_QUOTA; break;

        case ':': token.type = TOK_COLON; break;
        case ';': token.type = TOK_SEMICOLON; break;
        case ',': token.type = TOK_COMMA; break;

        case '=': token.type = TOK_EQUAL; break;
        case '+': token.type = TOK_PLUS; break;
        case '-': 
            if (peek() == '>') {
                token.type = TOK_ARROW;
                advance();
            } else token.type = TOK_MINUS; break;
        case '*': token.type = TOK_STAR; break;
        case '/': token.type = TOK_SLASH; break;

        case '>': token.type = TOK_GREATER; break;
        case '<': token.type = TOK_LESS; break;

        default: token.type = TOK_EOF; break;
    }

    return token;
}