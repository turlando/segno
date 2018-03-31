#ifndef __SEGNO_SHAPE_H__
#define __SEGNO_SHAPE_H__

#include <stdbool.h>
#include <libguile.h>
#include <linmath.h>
#include <GL/gl3w.h>

struct shape {
    int n;

    GLuint vertex_buffer;
    GLuint vertex_array;

    mat4x4 matrix;

    bool fill;
};

SCM shape_to_scm(struct shape shape);
struct shape scm_to_shape(SCM shape_scm);

#endif // __SEGNO_SHAPE_H__
