#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Determines the blocks reserved by realloc
// to store the tokens.
#define TOKENS_BLOCK 20

// Determines the token types of the language.
typedef enum {
    TOK_VARIABLE, TOK_FUN, TOK_RETURN, TOK_INT, TOK_FLOAT,
    TOK_ADD, TOK_SUB, TOK_MUL, TOK_DIV, TOK_LEFT_PAR,
    TOK_RIGHT_PAR, TOK_LEFT_BRACE, TOK_RIGHT_BRACE, TOK_SEMICOLON,
    TOK_INT_TYPE
} TokenType;

// Determines the structure of a given token.
typedef struct {
    // Stores the token type.
    TokenType type;
    // Stores the token string.
    char *string;
} Token;

typedef struct {
    // Stores the tokens (the result).
    Token *list;
    // Stores the ammount of tokens available.
    size_t count;
    // Stores the ammount of tokens that can be stored.
    size_t capacity;
} Tokens;

// Determines the structure of a given lexer.
typedef struct {
    // Stores the tokens (the result).
    Token tokens;
    // Stores the start and the current positions.
    //
    // let variable_name = 10
    //     |           |
    //   start      current
    char *start, *current;
    // Stores the source code.
    char *source;
} Lexer;

// Initiates the lexer by adding the source code there.
void lexer_init(Lexer *lexer, char *source);
// Scans the next token of the lexer and puts it into token.
// Returns false if token is not found.
bool lexer_next_token(Lexer *lexer, Token *token);
// Scans all the tokens and puts it to the tokens list.
void lexer_scan_all(Lexer *lexer, Tokens *tokens);
// Prints all the tokens.
void print_tokens(Tokens *tokens);
// Prints the given token.
void print_token(Token *token);

#endif
