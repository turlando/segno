#include <stdlib.h>
#include <libguile.h>
#include <shapes.h>
#include <utils.h>
#include <shape.h>
#include <shader.h>

SCM shape_fill(SCM shape_scm) {
    struct shape shape = scm_to_shape(shape_scm);
    shape.fill = true;

    return shape_to_scm(shape);
}

void shape_draw(SCM shape_scm, struct shader_program program) {
    if (scm_is_pair(shape_scm)) {
        SCM list = shape_scm;

        foreach(shape_scm, list) {
            shape_scm = scm_car(list);
            shape_draw(shape_scm, program);
        }

        return;
    }

    struct shape shape = scm_to_shape(shape_scm);

    glUseProgram(program.id);

    // cast to GLfloat array
    GLfloat matrix[16];
    for(int i=0; i<4; i++)
    for(int j=0; j<4; j++)
        matrix[i*4 + j] = shape.matrix[i][j];

    glUniformMatrix4fv(program.uniform_matrix, 1, GL_FALSE, matrix);

    glBindVertexArray(shape.vertex_array);

    if (shape.fill)
        glDrawArrays(GL_TRIANGLE_FAN, 0, shape.n);
    else
        glDrawArrays(GL_LINE_LOOP, 0, shape.n);

    glBindVertexArray(0);
    glUseProgram(0);
}
