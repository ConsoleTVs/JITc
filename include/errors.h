#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>

#define MAX_LINE_LENGTH 500

typedef enum {
    ERROR_UNKNOWN_TOKEN
} ErrorType;

int red_printf(const char *format, ...);
void error(ErrorType error, const char *file, uint32_t line, uint32_t col, const char *hint);

#endif
