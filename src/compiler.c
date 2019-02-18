#include "../include/compiler.h"
#include "../include/parser.h"

#include <stdlib.h>
#include <string.h>

void compiler_init(Compiler *compiler, char *file)
{
    compiler->file = malloc(sizeof(char) * strlen(file) + 1);
    strcpy(compiler->file, file);
}

void compiler_compile(Compiler *compiler)
{
    Parser parser;
    parser_init(&parser, compiler->file);
    AST ast;
    parser_parse(&parser, &ast);
}
