#ifndef __SEGNO_SHAPE_H__
#define __SEGNO_SHAPE_H__

#include <stdbool.h>
#include <libguile.h>
#include <linmath.h>
#include <GL/gl3w.h>
#include <polygon.h>

struct shape {
    GLuint vertex_count;
    GLuint vertex_buffer;
    GLuint vertex_array;
    GLuint begin_mode;
};

struct shape polygon_to_shape(struct polygon polygon);

#endif // __SEGNO_SHAPE_H__
