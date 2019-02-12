#include "../include/lexer.h"
#include "../include/errors.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IS_NUMBER(input) (input >= '0' && input <= '9')
#define IS_ALPHA(input) ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || input == '_')
#define IS_ALPHANUMERIC(input) (IS_NUMBER(input) || IS_ALPHA(input))
#define RESERVED_WORDS_NUM 3

static char *token_names[] = {
    "TOK_VARIABLE", "TOK_FUN", "TOK_RETURN", "TOK_INT", "TOK_FLOAT",
    "TOK_ADD", "TOK_SUB", "TOK_MUL", "TOK_DIV", "TOK_LEFT_PAR",
    "TOK_RIGHT_PAR", "TOK_LEFT_BRACE", "TOK_RIGHT_BRACE", "TOK_SEMICOLON",
    "TOK_INT_TYPE"
};

typedef struct { char *key; TokenType type; } ReservedWord;
static ReservedWord reserved_words[RESERVED_WORDS_NUM] = {
    { "fun", TOK_FUN }, { "return", TOK_RETURN }, { "int", TOK_INT_TYPE },
};

static void lexer_save_token(Lexer *lexer, Token *token, TokenType token_type) {
    // Set the token type.
    token->type = token_type;
    // Reserve the memory for the string.
    token->string = malloc(sizeof(char) * (lexer->current - lexer->start + 2));
    // Add the string to the token
    // This basically gets the substring from (lexer->start - lexer->source)
    // with a length of (lexer->current - lexer->start)
    memcpy(token->string, &lexer->source[lexer->start - lexer->source], lexer->current - lexer->start + 1);
    token->string[lexer->current - lexer->start + 1] = '\0';
    // Set the lexer start to the current char.
    lexer->start = lexer->current + 1;
}

static void lexer_is_number(Lexer *lexer, Token *token)
{
    // Add the whole number.
    while (IS_NUMBER(*lexer->current)) lexer->current++;
    // Check to see if there's decimals.
    if (*lexer->current == '.' && IS_NUMBER(*(lexer->current + 1))) {
        lexer->current++; // The .
        while (IS_NUMBER(*lexer->current)) lexer->current++;
        lexer_save_token(lexer, token, TOK_FLOAT);
    }
    lexer->current--;
    lexer_save_token(lexer, token, TOK_INT);
}

static void lexer_is_identifier(Lexer *lexer, Token *token)
{
    while (IS_ALPHANUMERIC(*lexer->current)) lexer->current++;
    lexer->current--;
    lexer_save_token(lexer, token, TOK_VARIABLE);
    // Check to see if it's a reserved key word
    for (uint8_t i = 0; i < RESERVED_WORDS_NUM; i++) {
        // Compare both strings to see if they match.
        if (strcmp(reserved_words[i].key, token->string) == 0) {
            // We found an ocurrence. Replace the type
            token->type = reserved_words[i].type;
        }
    }
}

void lexer_init(Lexer *lexer, char *source)
{
    // Set the source to the lexer.
    lexer->source = source;
    // Set the lexer start char.
    lexer->current = source;
    lexer->start = source;
}

bool lexer_next_token(Lexer *lexer, Token *token)
{
    if (*lexer->current == '\0') return false;
    // We scan a token here.
    lexer_next_token_switch:
    switch (*lexer->current) {
        case '\n': case '\r': { break; }
        case ' ': { lexer->start++; lexer->current++; goto lexer_next_token_switch; }
        case '+': { lexer_save_token(lexer, token, TOK_ADD); break; }
        case '-': { lexer_save_token(lexer, token, TOK_SUB); break; }
        case '*': { lexer_save_token(lexer, token, TOK_DIV); break; }
        case '/': { lexer_save_token(lexer, token, TOK_MUL); break; }
        case '(': { lexer_save_token(lexer, token, TOK_LEFT_PAR); break; }
        case ')': { lexer_save_token(lexer, token, TOK_RIGHT_PAR); break; }
        case '{': { lexer_save_token(lexer, token, TOK_LEFT_BRACE); break; }
        case '}': { lexer_save_token(lexer, token, TOK_RIGHT_BRACE); break; }
        case ';': { lexer_save_token(lexer, token, TOK_SEMICOLON); break; }
        default: {
            // Determine if it's a number or an identifier.
            if (IS_NUMBER(*lexer->current)) { lexer_is_number(lexer, token); break; }
            else if (IS_ALPHA(*lexer->current)) { lexer_is_identifier(lexer, token); break; }
            error(ERROR_UNKNOWN_TOKEN, "test.txt", 3, "Check if the token exists");
        }
    }
    lexer->current++;
    // Returning true as token is OK.
    return true;
}

void lexer_scan_all(Lexer *lexer, Tokens *tokens)
{
    // Reserve the memory where the tokens will be stored.
    tokens->list = malloc(sizeof(Token) * TOKENS_BLOCK);
    tokens->count = 0;
    tokens->capacity = TOKENS_BLOCK;
    while (lexer_next_token(lexer, &tokens->list[tokens->count])) {
        if (tokens->capacity < tokens->count + 1) {
            tokens = realloc(tokens, sizeof(Token) * (tokens->capacity += TOKENS_BLOCK));
        }
        tokens->count++;
    }
}

void print_tokens(Tokens *tokens)
{
    for (size_t i = 0; i < tokens->count; i++) print_token(&tokens->list[i]);
}

void print_token(Token *token)
{
    printf("{ type: %s, string: %s }\n", token_names[token->type], token->string);
}

#undef IS_NUMBER
#undef IS_ALPHA
#undef IS_ALPHANUMERIC
