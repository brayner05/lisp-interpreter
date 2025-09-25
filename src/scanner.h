#ifndef LISP_SCANNER_H
#define LISP_SCANNER_H
#include <stdint.h>
#include <stdlib.h>

typedef enum {
    TOKEN_LPAREN, TOKEN_RPAREN,
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_ASTERISK, TOKEN_SLASH,
    TOKEN_NUMBER, TOKEN_STRING, TOKEN_TRUE, TOKEN_FALSE,
    TOKEN_DEFINE, TOKEN_VAR,
    TOKEN_EOF
} TokenType;

typedef struct Token {
    char *start;
    size_t length;
    struct Token *next;
    struct Token *prev;
} Token;

#endif