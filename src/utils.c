#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <utils.h>
#include <linmath.h>

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

    vsnprintf(str, size, fmt, args);

    return str;
}

/**
 * Convert a mat4x4 to a vector of floats.
 * The pointer should be passed to free(3) when
 * no longer needed.
 */
float *mat4x4_to_floats_new(mat4x4 in) {
    float *out = malloc(sizeof(float) * 16);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out[i * 4 + j] = in[i][j];
        }
    }

    return out;
}
