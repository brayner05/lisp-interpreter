#ifndef LISP_PARSER_H
#define LISP_PARSER_H
#include "common.h"
#include "../scanner/scanner.h"

struct Expression;

typedef struct ParserResult {
    bool success;
    union {
        struct Expression *root_node;
        Error error;
    };
} ParserResult;


typedef struct Operation {
    TokenType operation;
    struct Expression *operand_list;
    struct Expression *last_operand;
} Operation;

typedef enum OperandType {
    OPERAND_NUMBER, OPERAND_STRING,
    OPERAND_TRUE, OPERAND_FALSE,
    OPERAND_IDENTIFIER,
    OPERAND_EXPRESSION
} OperandType;

typedef struct Operand {
    enum OperandType type;
    union {
        int32_t numeric;
        char *string;
        bool boolean;
        char *identifier;
        struct Expression *expression;
    };
} Operand;

typedef struct FunctionDefinition {
    char *name;
    char **parameters;
    struct Expression *body;
} FunctionDefinition;

typedef enum ExpressionType {
    EXPR_OPERATION,
    EXPR_FUNCTION,
    EXPR_OPERAND
} ExpressionType;

typedef struct Expression {
    enum ExpressionType type;
    union {
        Operand *operand;
        Operation *operation;
        FunctionDefinition *function;
    };
} Expression;

extern ParserResult evaluate(Token *token_list);

#endif