#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "lexer.h"

typedef enum {
    INT,
    FLOAT,
    STRING,
    CHAR,
    BOOL,
} VarTypes;

typedef struct {
    char *name;
    VarTypes type;
    union {
        int int_value;
        float float_value;
        char *string_value;
        bool boolean_value;
    } value;
} VarEnvironment;

void parser_init(const char *src);
void parser_threads(void);