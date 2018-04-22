#ifndef __SEGNO_SHAPE_H__
#define __SEGNO_SHAPE_H__

#include <stdbool.h>
#include <linmath.h>
#include <GL/gl3w.h>
#include <polygon.h>
#include <transformation.h>

static const char shape_vertex_shader[] =
    "#version 330\n"
    "layout(location = 0) in vec2 point;\n"
    "uniform mat4 matrix;\n"
    "void main() {\n"
    "    gl_Position = matrix * vec4(point, 0.0, 1.0);\n"
    "}\n";

static const char shape_fragment_shader[] =
    "#version 330\n"
    "out vec4 color;\n"
    "void main() {\n"
    "    color = vec4(0.9, 0.9, 0.9, 0);\n"
    "}\n";

struct shape {
    GLuint vertex_count;
    GLuint vertex_buffer;
    GLuint vertex_array;
    GLuint begin_mode;
    mat4x4 matrix;
};

struct shape shape(struct polygon polygon, struct transformations ts);

#endif // __SEGNO_SHAPE_H__
