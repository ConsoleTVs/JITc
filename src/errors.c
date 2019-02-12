#include "../include/errors.h"

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

static const char *error_get_string(ErrorType error)
{
    switch (error) {
        case ERROR_UNKNOWN_TOKEN: { return "Unknown Token"; }
    }
}

static const char *error_get_description(ErrorType error)
{
    switch (error) {
        case ERROR_UNKNOWN_TOKEN: { return "An unknown token was found during the scanning of the file."; }
    }
}

void error(ErrorType error, const char *file, uint32_t line, const char *hint)
{
    // Get the command line specifications.
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // Format the error
    char *line = malloc(sizeof(char) * w.ws_col);
    char *error = generate_error(error);
    char *filler = malloc(sizeof(char) * (w.ws_col - strlen(error)));
    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
}