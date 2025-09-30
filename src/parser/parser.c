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

inline static ParserResult error(char *message) {
    Error error = { 
        .column = peek() != NULL ? peek()->column : 0, 
        .message = message 
    };

    ParserResult result = { 
        .success = false, 
        .error = error 
    };

    return result;
}

inline static ParserResult success(void) {
    ParserResult result = { .success = true, .root_node = NULL };
    return result;
}

static bool consume(TokenType type) {
    if (peek() == NULL)
        return false;

    if (peek()->type != type)
        return false;
        
    next();
    return true;
}

static ParserResult operation(void) {
    next();
    return success();
}

static ParserResult expression(void) {
    if (!consume(TOKEN_LPAREN))
        return error("Expected '('");

    switch (peek()->type) {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
        case TOKEN_ASTERISK:
        case TOKEN_SLASH: {
            return operation();
        }
    }

    if (!consume(TOKEN_RPAREN))
        return error("Expected ')'");
}

extern ParserResult evaluate(Token *token_list) {
    next_token = token_list;
    return expression();
}