#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Determines the blocks reserved by realloc to store the tokens.
#define TOKENS_BLOCK 20

// Determines the token types of the language.
typedef enum {
    TOK_VARIABLE, TOK_FUN, TOK_RETURN, TOK_INT, TOK_FLOAT,
    TOK_EQ, TOK_ADD, TOK_SUB, TOK_MUL, TOK_DIV, TOK_LEFT_PAR,
    TOK_RIGHT_PAR, TOK_LEFT_BRACE, TOK_RIGHT_BRACE, TOK_SEMICOLON, TOK_COMMA,
    TOK_INT_TYPE, TOK_FLOAT_TYPE, TOK_EOF
} TokenType;

// Determines the structure of a given token.
typedef struct {
    // Stores the token type.
    TokenType type;
    // Stores the token string.
    char *string;
    // Stores the line and the col they were found at.
    uint32_t line, col;
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
    // Stores the start and the current positions.
    //
    // int variable_name = 10
    //     |           |
    //   start      current
    char *start, *current;
    // Stores the source code and the file name-
    char *source, *file;
    // Stores the current scanner line and col.
    uint32_t line, col;
} Lexer;

// Initiates the lexer by adding the source code there.
void lexer_init(Lexer *lexer, char *source, char *file);
// Initiates the lexer given a source file path.
void lexer_init_file(Lexer *lexer, char *file);
// Scans the next token of the lexer and puts it into token. Returns false if token is EOF.
bool lexer_next_token(Lexer *lexer, Token *token);
// Scans all the tokens and puts it to the tokens list.
void lexer_scan_all(Lexer *lexer, Tokens *tokens);
// Removes the lexer memory.
void lexer_delete(Lexer *lexer);

// Initialize the tokens to a zero state.
void tokens_init(Tokens *tokens);
// Initialize the tokens inside the tokens list given the offset till the end.
void tokens_init_tokens(Tokens *tokens, size_t start_at);
// Prints all the tokens.
void tokens_print(Tokens *tokens);
// Removes the tokens list.
void tokens_delete(Tokens *tokens);

// Removes the token.
void token_delete(Token *token);
// Initializes the token to a zero state.
void token_init(Token *token);
// Prints the given token.
void token_print(Token *token);

#endif
