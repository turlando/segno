#ifndef __SEGNO_SHADER_H__
#define __SEGNO_SHADER_H__

#include <GL/gl3w.h>

GLuint shader_program_new(const GLchar *vert_shader,
                          const GLchar *frag_shader);

#endif // __SEGNO_SHADER_H__
