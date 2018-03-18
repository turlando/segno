#pragma once

#include <GL/gl3w.h>

struct shader_program {
    GLuint id;
    GLuint uniform_matrix;
};

struct shader_program shader_program_new(const GLchar *vert_shader,
                                         const GLchar *frag_shader);
void shader_program_free(struct shader_program program);
