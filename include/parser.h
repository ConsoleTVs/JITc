#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Determines the blocks reserved by realloc
// to store the AST.
#define AST_BLOCK 20

typedef enum {
    ST_FUNCTION, ST_RETURN, ST_EXPRESSION
} StatementType;

typedef enum {
    EX_INT, EX_FLOAT, EX_VARIABLE,
    EX_UNARY, EX_BINARY
} ExpressionType;

struct Expression;

typedef struct {
    Token op;
    struct Expression *expression;
} UnaryValue;

void value_create_unary(Token op, struct Expression *expression);

typedef struct {
    Token op;
    struct Expression *left, *right;
} BinaryValue;

typedef struct Expression {
    ExpressionType type;
    union {
        int64_t int_value;
        float float_value;
        char *variable_value;
    };
} Expression;

typedef struct {
    StatementType type;
    union {
        char *fun_name;
        Expression *expression;
    };
} Statement;

typedef struct {
    Statement *statements;
    uint64_t count, capacity;
} AST;

typedef struct {
    char *file;
    Lexer lexer;
    Token current, lookahead;
} Parser;

void parser_init(Parser *parser, char *file);
void parser_parse(Parser *parser, AST *ast);
void parser_delete(Parser *parser);

void ast_init(AST *ast);
void ast_delete(AST *ast);

void statement_delete(Statement *statement);

#endif
