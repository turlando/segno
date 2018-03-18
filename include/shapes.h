#pragma once

#include <stdbool.h>
#include <libguile.h>
#include <linmath.h>
#include <GL/gl3w.h>
#include <shader.h>

struct shape {
    int n;
    GLuint vertex_buffer;
    GLuint vertex_array;
    mat4x4 matrix;

    bool fill;
};

void shape_draw(SCM shape, struct shader_program program);
SCM shape_to_scm(struct shape shape);
struct shape scm_to_shape(SCM shape_scm);
