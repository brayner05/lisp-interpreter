#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "scanner.h"

static char *source_str = NULL;
static size_t source_length = 0;
static uint64_t current = 0;
static uint64_t start = 0;
static Token *token_list = NULL;
static Token *token_list_end = NULL;

static bool has_next(void) {
    return current < source_length;
}

static void append_token(Token *token) {
    if (token_list == NULL) {
        token_list_end = token_list = token;
        return;
    }

    if (token_list == token_list_end) {
        token_list_end = token;
        token_list->next = token_list_end;
        token_list_end->prev = token_list;
        return;
    }

    token->prev = token_list_end;
    token_list_end->next = token;
    token_list_end = token;
}

static bool append_eof_token(void) {
    Token *eof_token = (Token *) malloc(sizeof(Token));
    if (eof_token == NULL)
        return false;

    eof_token->next = eof_token->prev = NULL;
    eof_token->type = TOKEN_EOF;
    eof_token->start = NULL;
    eof_token->length = 0;
    append_token(eof_token);

    return true;
}

static char peek(void) {
    if (!has_next())
        return '\0';
    return source_str[current];
}

static char next(void) {
    return source_str[current++];
}

static void scan_next(void) {
    char ch = next();
    switch (ch) {
        default: {
            break;
        }
    }
}

extern Token *lisp_tokenize(char *source, size_t length) {
    // Disallow NULL.
    if (source == NULL) 
        return NULL;

    // Initialize the lexer.
    source_str = source;
    source_length = length;
    current = start = 0;
    token_list = NULL;

    while (has_next()) {
        scan_next();
        start = current;
    }

    append_eof_token();
    return token_list;
}