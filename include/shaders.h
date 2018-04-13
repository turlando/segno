#ifndef __SEGNO_SHADERS_H__
#define __SEGNO_SHADERS_H__

const char vertex_shader[] =
    "#version 330\n"
    "layout(location = 0) in vec2 point;\n"
    "uniform mat4 matrix;\n"
    "void main() {\n"
    "    gl_Position = matrix * vec4(point, 0.0, 1.0);\n"
    "}\n";

const char fragment_shader[] =
    "#version 330\n"
    "out vec4 color;\n"
    "void main() {\n"
    "    color = vec4(0.9, 0.9, 0.9, 0);\n"
    "}\n";

#endif // __SEGNO_SHADERS_H__
