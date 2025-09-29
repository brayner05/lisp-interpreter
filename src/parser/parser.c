#include "parser.h"

Token *next_token = NULL;

inline static Token *next(void) {
    Token *current = next_token;
    next_token = next_token->next;
    return current;
}

inline static Token *peek(void) {
    return next_token;
}

static void consume(TokenType type, char *error_message) {
    if (peek()->type == type)
        return; // Success
    else
        return; // Error
}

static Operation *operation(void) {

}

static Expression expression(void) {
    consume(TOKEN_LPAREN, "Expected '('");
    consume(TOKEN_RPAREN, "Expected ')'");
}

extern Expression evaluate(Token *token_list) {
    next_token = token_list;
    return expression();
}