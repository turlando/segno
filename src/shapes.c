#include <stdlib.h>
#include <math.h>
#include <linmath.h>
#include <GL/gl3w.h>
#include <shapes.h>
#include <utils.h>
#include <shape.h>

/**
 * Return an array of size (n * 2) storing the coordinates (x, y)
 * of the vertices of a regular polygon with (n) sides.
 * The pointer should passed to free(3) when it is no longer needed.
 */
float *polygon_vertices(int n) {
    float *array = malloc(sizeof(float) * n * 2);

    int i;
    float t;

    for (i = 0; i < n; i++) {
        t = i * (2 * M_PI / n) + (M_PI / 2);

        array[i * 2]    = cos(t);
        array[i * 2 +1] = sin(t);
    }

    return array;
}

struct shape shape_polygon(int n) {
    // Create a new vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Make it the active array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Compute the vertices
    float *vertices = polygon_vertices(n);
    size_t vertices_size = sizeof(float) * n * 2;

    // Copy the vertices data to the active array buffer
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

    // From now on we don't need the vertices anymore
    // since they're stored in the graphic card memory
    free(vertices);

    // Create a new vertex array object
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // Make it the active array object
    glBindVertexArray(vao);

    // Define how the vertices are packed in memory
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // Release the active array buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Release the active array object
    glBindVertexArray(0);

    struct shape shape;
    shape.n = n;
    shape.vertex_buffer = vbo;
    shape.vertex_array = vao;
    mat4x4_identity(shape.matrix);
    shape.fill = false;

    return shape;
}
