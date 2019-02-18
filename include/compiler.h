#ifndef COMPILER_H
#define COMPILER_H

typedef struct {
    char *file;
} Compiler;

void compiler_init(Compiler *compiler, char *file);
void compiler_compile(Compiler *compile);

#endif
