#include <stdio.h>
#include <stdlib.h>
#include <GL/gl3w.h>
#include <shader.h>

/**
 * @param type   Can either be GL_VERTEX_SHADER or GL_FRAGMENT_SHADER
 * @param source A string containing the shader source code
 */
static GLuint compile(GLenum type, const GLchar *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status != GL_TRUE) {
        fprintf(stderr, "Error compiling %s shader",
                (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
        exit(EXIT_FAILURE);
    }

    return shader;
}

static GLuint link(GLuint vert, GLuint frag) {
    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status != GL_TRUE) {
        fprintf(stderr, "Error linking shader program");
        exit(EXIT_FAILURE);
    }

    return program;
}

struct shader_program shader_program_new(const GLchar *vert_shader,
                                         const GLchar *frag_shader) {
    GLuint vert = compile(GL_VERTEX_SHADER, vert_shader);
    GLuint frag = compile(GL_FRAGMENT_SHADER, frag_shader);
    GLuint prog = link(vert, frag);

    glDeleteShader(vert);
    glDetachShader(prog, vert);

    glDeleteShader(frag);
    glDetachShader(prog, frag);

    struct shader_program program;
    program.id = prog;
    program.uniform_matrix = glGetUniformLocation(program.id, "matrix");

    return program;
}

void shader_program_free(struct shader_program program) {
    glDeleteProgram(program.id);
}
