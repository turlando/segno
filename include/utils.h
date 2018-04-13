#ifndef __SEGNO_UTILS_H__
#define __SEGNO_UTILS_H__

#include <linmath.h>

#define M_PI 3.141592653589793

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

char *vasnprintf(const char *fmt, ...);
float *mat4x4_to_floats_new(mat4x4 in);

#endif // __SEGNO_UTILS_H__
