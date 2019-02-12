#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>

typedef enum {
    ERROR_UNKNOWN_TOKEN
} ErrorType;

void error(ErrorType error, const char *file, uint32_t line, const char *hint);

#endif
