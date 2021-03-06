/**
 * |----------------------------------------------------------|
 * | JITc - A very simple and efficient JIT compiled language |
 * |----------------------------------------------------------|
 *
 * Copyright (c) 2019 Erik Campobadal <soc@erik.cat>
 * https://erik.cat
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "include/lexer.h"
#include "include/parser.h"
#include "include/compiler.h"
#include "include/errors.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // Check the command line arguments.
    if (argc < 2) {
        red_printf(" > ");
        printf("The command line usage is: path/to/executable path/to/source\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the lexer
    Lexer lexer;
    lexer_init_file(&lexer, argv[1]);
    // Initialize the tokens
    Tokens tokens;
    tokens_init(&tokens);
    // Scan all the tokens.
    lexer_scan_all(&lexer, &tokens);
    tokens_print(&tokens);

    // Initialize the parser.
    Parser parser;
    parser_init(&parser, argv[1]);
    return 0;
}
