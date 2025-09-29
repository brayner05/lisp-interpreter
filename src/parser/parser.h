#ifndef LISP_PARSER_H
#define LISP_PARSER_H
#include "common.h"
#include "../scanner/scanner.h"

struct Expression;

typedef enum Operator {
    OPERATOR_PLUS, OPERATOR_MINUS,
    OPERATOR_MULT, OPERATOR_DIV,
    OPERATOR_PRINT
} Operator;

typedef struct Operation {
    enum Operator operation;
    struct Expression *operand_list;
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

extern Expression evaluate(Token *token_list);

#endif