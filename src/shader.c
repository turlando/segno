#include <stdio.h>
#include <stdlib.h>
#include <GL/gl3w.h>
#include <shader.h>

static GLuint compile(GLenum type, const GLchar *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    GLint param;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
    if (!param) {
        GLchar log[4096];
        glGetShaderInfoLog(shader, sizeof(log), NULL, log);
        fprintf(stderr, "GL3W: %s: %s\n",
                type == GL_FRAGMENT_SHADER ? "frag" : "vert", (char *) log);
        exit(EXIT_FAILURE);
    }
    return shader;
}

static GLuint link(GLuint vert, GLuint frag) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);
    GLint param;
    glGetProgramiv(program, GL_LINK_STATUS, &param);
    if (!param) {
        GLchar log[4096];
        glGetProgramInfoLog(program, sizeof(log), NULL, log);
        fprintf(stderr, "GL3W: link: %s\n", (char *) log);
        exit(EXIT_FAILURE);
    }
    return program;
}

struct shader_program shader_program_new(const GLchar *vert_shader,
                                         const GLchar *frag_shader) {
    struct shader_program program;

    GLuint vert = compile(GL_VERTEX_SHADER, vert_shader);
    GLuint frag = compile(GL_FRAGMENT_SHADER, frag_shader);

    program.id = link(vert, frag);

    glDeleteShader(frag);
    glDeleteShader(vert);

    program.uniform_matrix = glGetUniformLocation(program.id, "matrix");

    return program;
}

void shader_program_free(struct shader_program program) {
    glDeleteProgram(program.id);
}
