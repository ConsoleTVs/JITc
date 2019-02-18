#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/errors.h"
#include <stdlib.h>
#include <string.h>

#define IS_AT_END() (parser->current.type == TOK_EOF)
#define NEXT() lexer_next_token(&parser->lexer, &parser->current)

void parser_init(Parser *parser, char *file)
{
    parser->file = malloc(sizeof(char) * strlen(file) + 1);
    strcpy(parser->file, file);
    // Initialize the tokens.
    token_init(&parser->current);
    token_init(&parser->lookahead);
    // Initialize the lexer.
    lexer_init_file(&parser->lexer, parser->file);
}

static void parser_consume(Parser *parser, TokenType type, ErrorType err, char *hint)
{
    if (parser->current.type == type) {
        NEXT();
        return;
    }

    show_error(err, parser->file, parser->current.line, parser->current.col, hint);
    exit(EXIT_FAILURE);
}

static bool parser_match(Parser *parser, TokenType type)
{
    if (parser->current.type == type) {
        if (parser->current.type != TOK_EOF) NEXT();
        return true;
    }

    return false;
}

void parser_parse(Parser *parser, AST *ast)
{
    // Reserve memory for the AST.
    ast->capacity = AST_BLOCK;
    ast->count = 0;
    ast->statements = malloc(sizeof(Statement) * AST_BLOCK);

    while (!IS_AT_END()) {
        switch (parser->current.type) {
            case TOK_FUN: {
                // Parsing a function.
                // fun <name>([<arguments>]) { [<statements>] }
                break;
            }
        }
    }
}

void parser_delete(Parser *parser)
{
    free(parser->file);
    lexer_delete(&parser->lexer);
}

void ast_init(AST *ast)
{
    ast->count = 0;
    ast->capacity = 0;
    ast->statements = NULL;
}

void ast_delete(AST *ast)
{
    for (size_t i = 0; i < ast->count; i++) statement_delete(&ast->statements[i]);
    free(ast->statements);
}

void statement_delete(Statement *statement)
{
    switch (statement->type) {
        case ST_FUNCTION: {
            free(statement->fun_name);
            break;
        }
        case ST_RETURN: case ST_EXPRESSION: {
            free(statement->expression);
            break;
        }
    }
}
