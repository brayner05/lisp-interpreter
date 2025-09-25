#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include "scanner.h"

static char *source_str = NULL;
static size_t source_length = 0;
static uint64_t current = 0;
static uint64_t start = 0;
static Token *token_list = NULL;
static Token *token_list_end = NULL;
static Token eof_token = { .type = TOKEN_EOF, .length = 0, .next = NULL, .prev = NULL, .start = NULL };

#ifdef LISP_DEBUG

/// @brief A map containing stringified names for each type of token.
static const char *token_names[] = {
    [TOKEN_LPAREN] = "LPAREN",
    [TOKEN_RPAREN] = "RPAREN",
    [TOKEN_PLUS] = "PLUS",
    [TOKEN_MINUS] = "MINUS",
    [TOKEN_ASTERISK] = "ASTERISK",
    [TOKEN_SLASH] = "SLASH",
    [TOKEN_NUMBER] = "NUMBER",
    [TOKEN_STRING] = "STRING",
    [TOKEN_TRUE] = "TRUE",
    [TOKEN_FALSE] = "FALSE",
    [TOKEN_DEFINE] = "DEFINE",
    [TOKEN_VAR] = "VAR",
    [TOKEN_EOF] = "EOF"
};

extern const char *token_name(Token *token) {
    size_t type_index = (size_t) token->type;
    return token_names[type_index];
}

#endif

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

static Token *create_token(TokenType type) {
    Token *token = (Token *) malloc(sizeof(Token));
    if (token == NULL)
        return NULL;

    token->type = type;
    token->start = &source_str[start];
    token->length = current - start;
    token->next = token->prev = NULL;

    return token;
}

static char peek(void) {
    if (!has_next())
        return '\0';
    return source_str[current];
}

static char next(void) {
    return source_str[current++];
}

static void scan_number(void) {
    // Read until finding a non-digit character.
    while (has_next() && isdigit(peek())) 
        next();

    // If the character is a dot, pass it, and continue reading digits.
    if (has_next() && peek() == '.') {
        next();
        while (has_next() && isdigit(peek())) 
            next();
    }

    Token *token = create_token(TOKEN_NUMBER);
    append_token(token);
}

static void scan_next(void) {
    Token *token = NULL;

    char ch = next();
    switch (ch) {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            break;

        case '(': {
            token = create_token(TOKEN_LPAREN);
            break;
        }

        case ')': {
            token = create_token(TOKEN_RPAREN);
            break;
        }

        case '+': {
            token = create_token(TOKEN_PLUS);
            break;
        }

        case '-': {
            token = create_token(TOKEN_MINUS);
            break;
        }

        case '*': {
            token = create_token(TOKEN_ASTERISK);
            break;
        }

        case '/': {
            token = create_token(TOKEN_SLASH);
            break;
        }

        default: {
            if (isdigit(ch)) {
                scan_number();
                break;
            }
            break;
        }
    }

    if (token != NULL)
        append_token(token);
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

    append_token(&eof_token);
    return token_list;
}