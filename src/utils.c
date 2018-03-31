#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <utils.h>

/**
 * Return the pointer to an allocated string in a buffer
 * large enough to hold the formatted string including the
 * terminating NULL byte.
 * The pointer should be passed to free(3) when the string
 * is no longer needed.
 */
char *vasnprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    size_t size = vsnprintf(NULL, 0, fmt, args) + 1;
    char *str = malloc(size);

    snprintf(str, size, fmt, args);

    return str;
}
