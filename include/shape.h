#pragma once

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

struct shape shape_polygon(int n);
SCM shape_to_scm(struct shape shape);
struct shape scm_to_shape(SCM shape_scm);
