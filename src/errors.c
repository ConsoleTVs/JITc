#include "../include/errors.h"

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#endif
#include <stdio.h>
#include <stdarg.h>

static const char *error_get_string(ErrorType error)
{
    switch (error) {
        case ERROR_UNKNOWN_TOKEN: return "UNKNOWN TOKEN";
        default: return "UNKNOWN ERROR";
    }
}

static const char *error_get_description(ErrorType error)
{
    switch (error) {
        case ERROR_UNKNOWN_TOKEN: return "An unknown token was found during the scanning of the file.";
        default: return "No description provided";
    }
}

int red_printf(const char *format, ...)
{
    va_list arg;
    int done;
    va_start(arg, format);

    #if defined(_WIN32) || defined(_WIN64)
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD saved_attributes;
        /* Save current attributes */
        GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
        saved_attributes = consoleInfo.wAttributes;
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        done = vfprintf(stderr, format, arg);
        /* Restore original attributes */
        SetConsoleTextAttribute(hConsole, saved_attributes);
    #else
        char *fmt = malloc(sizeof(char) * (strlen(format) + 10)); // \x1b[31m\x1b[0m = (9 + '\0')
        strcpy(fmt, "\x1b[31m");
        strcat(fmt, format);
        strcat(fmt, "\x1b[0m");
        done = vfprintf(stderr, fmt, arg);
    #endif

    va_end(arg);

    return done;
}

// -- error_string ---------- file
//
// error_description
//
// XXX | source_line
//
// Hint: hint
void error(ErrorType error, const char *file, uint32_t line, uint32_t col, const char *hint)
{
    // Output the first line.
    red_printf("\n -- %s --------------- %s at line %d\n", error_get_string(error), file, line);
    // Output the error message.
    printf("\n %s\n", error_get_description(error));
    // Output the source file line.
    FILE *source_file = fopen(file, "r");
    if (source_file == NULL) {
        red_printf(" > ");
        printf("Unable to open the file '%s'\n", file);
        exit(EXIT_FAILURE);
    }
    char buffer[MAX_LINE_LENGTH];
    for (size_t current_line = 0; current_line <= line; current_line++) {
        error_read_again:
        fgets(buffer, sizeof(buffer), source_file);
        if (buffer == NULL) {
            red_printf(" > ");
            printf("Unable to open the file '%s'\n", file);
            exit(EXIT_FAILURE);
        }
        if (*buffer == EOF) {
            red_printf(" > ");
            printf("Line %d was not found in file '%s'\n", line, file);
            exit(EXIT_FAILURE);
        }
        if (strlen(buffer) == MAX_LINE_LENGTH && buffer[strlen(buffer) - 1] != '\n') {
            goto error_read_again;
        }
    }
    fclose(source_file);
    printf("\n %d | %s", line, buffer);
    size_t spaces = 4;
    // Raw speed to calculate the numbers of digits.
    // If you have more than 1000000000 lines in a file you should delete your code.
    if (line < 10) spaces += 1;
    else if (line < 100) spaces += 2;
    else if (line < 1000) spaces += 3;
    else if (line < 10000) spaces += 4;
    else if (line < 100000) spaces += 5;
    else if (line < 1000000) spaces += 6;
    else if (line < 10000000) spaces += 7;
    else if (line < 100000000) spaces += 8;
    else if (line < 1000000000) spaces += 9;
    for (size_t i = 0; i < col + spaces; i++) printf(" ");
    red_printf("^");
    printf("\n Hint: %s\n", hint);
}
