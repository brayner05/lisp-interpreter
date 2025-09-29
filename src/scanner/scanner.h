#ifndef LISP_SCANNER_H
#define LISP_SCANNER_H
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "common.h"

typedef enum {
    TOKEN_LPAREN, TOKEN_RPAREN,
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_ASTERISK, TOKEN_SLASH,
    TOKEN_NUMBER, TOKEN_STRING, TOKEN_TRUE, TOKEN_FALSE,
    TOKEN_DEFINE, TOKEN_VAR, TOKEN_IDENTIFIER,
    TOKEN_EOF
} TokenType;

typedef struct Token {
    TokenType type;
    char *start;
    size_t length;
    struct Token *next;
    struct Token *prev;
} Token;

typedef struct ScanResult {
    bool success;
    union {
        Error error;
        Token *token_list;
    };
} ScanResult;

extern ScanResult lisp_tokenize(char *source, size_t length);

#ifdef LISP_DEBUG
extern const char *token_name(Token *token);
#endif

#endif