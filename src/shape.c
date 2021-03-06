#include <stdlib.h>
#include <string.h>
#include <linmath.h>
#include <shape.h>
#include <polygon.h>
#include <transformation.h>

static struct shape polygon_to_shape(struct polygon polygon) {
    // Create a new vertex buffer object
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Make it the active array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Compute the vertices
    float *vertices = polygon_vertices_new(polygon.sides);
    size_t vertices_size = polygon_vertices_size(polygon.sides);

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

    GLuint begin_mode = polygon.fill == true ? GL_TRIANGLE_FAN : GL_LINE_LOOP;

    struct shape shape = {
        .vertex_count = polygon.sides,
        .vertex_buffer = vbo,
        .vertex_array = vao,
        .begin_mode = begin_mode
    };

    return shape;
}

struct shape shape(struct polygon polygon, struct transformations ts) {
    struct shape shape = polygon_to_shape(polygon);

    mat4x4 *mat = transformations_to_mat4x4(ts);
    memcpy(shape.matrix, mat, sizeof(mat4x4));

    return shape;
}
