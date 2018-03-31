#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <utils.h>

char *vasnprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    size_t size = vsnprintf(NULL, 0, fmt, args) + 1;
    char *str = malloc(size);

    snprintf(str, size, fmt, args);

    return str;
}
