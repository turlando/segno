#include <libguile.h>
#include <shape.h>
#include <math.h>
#include <utils.h>
#include <GL/gl3w.h>

SCM shape_to_scm(struct shape shape) {
    size_t size = sizeof(struct shape);
    struct shape *shape_in_heap = scm_gc_malloc_pointerless(size, "shape");

    memcpy(shape_in_heap, &shape, size);
    return scm_from_pointer(shape_in_heap, NULL);
}

struct shape scm_to_shape(SCM shape_scm) {
    struct shape *shape_ref = scm_to_pointer(shape_scm);
    struct shape shape = *shape_ref;
    return shape;
}

struct shape shape_polygon(int n) {
    float array[2*n];

    int i; float t;
    for (i = 0; i < n; i++) {
        t = i * (2 * M_PI / n) + M_PI / 2;
        array[i*2] = cos(t);
        array[i*2 +1] = sin(t);
    }

    GLuint vbo_point;
    GLuint vao_point;

    glGenBuffers(1, &vbo_point);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_point);
    glBufferData(GL_ARRAY_BUFFER, (2 * n * sizeof(float)), array, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao_point);
    glBindVertexArray(vao_point);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_point);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    struct shape shape;
    shape.n = n;
    shape.vertex_buffer = vbo_point;
    shape.vertex_array = vao_point;
    mat4x4_identity(shape.matrix);
    shape.fill = false;

    return shape;
}
