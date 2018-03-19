#ifndef __SEGNO_SHADER_H__
#define __SEGNO_SHADER_H__

#include <GL/gl3w.h>

struct shader_program {
    GLuint id;
    GLuint uniform_matrix;
};

struct shader_program shader_program_new(const GLchar *vert_shader,
                                         const GLchar *frag_shader);
void shader_program_free(struct shader_program program);


#endif // __SEGNO_SHADER_H__
