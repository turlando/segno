#include <stdio.h>
#include <stdlib.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <utils.h>
#include <window.h>
#include <shader.h>
#include <shape.h>

static void glfw_init() {
    if (glfwInit() != GLFW_TRUE) {
        fprintf(stderr, "GLFW3: initialization failed\n");
        exit(EXIT_FAILURE);
    }
}

static void gl3w_init() {
    if (gl3wInit()) {
        fprintf(stderr, "GL3W: initialization failed\n");
        exit(EXIT_FAILURE);
    }
}

static void glfw_window_init() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

static GLFWwindow *window_new(int width, int height, const char *title) {
    GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Error creating window");
        exit(EXIT_FAILURE);
    }
    return window;
}

static void resize_callback(GLFWwindow* window, int width, int height) {
    (void) window;

    int side = MAX(width, height);
    int x0 = (width - side) / 2;
    int y0 = (height - side) / 2;

    glViewport(x0, y0, side, side);
}

static void key_callback(GLFWwindow *window,
                         int key, int scancode,
                         int action, int mods) {
    (void) scancode;
    (void) mods;

    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void draw(struct shape shape, GLuint program) {
    glUseProgram(program);

    // Cast to GLfloat array
    GLfloat matrix[16];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i * 4 + j] = shape.matrix[i][j];
        }
    }

    GLuint uniform_matrix = glGetUniformLocation(program, "matrix");
    glUniformMatrix4fv(uniform_matrix, 1, GL_FALSE, matrix);
    glBindVertexArray(shape.vertex_array);

    if (shape.fill)
        glDrawArrays(GL_TRIANGLE_FAN, 0, shape.n);
    else
        glDrawArrays(GL_LINE_LOOP, 0, shape.n);

    glBindVertexArray(0);
    glUseProgram(0);
}

void window_loop() {
    glfw_init();
    glfw_window_init();

    GLFWwindow *window = window_new(640, 640, "Segno");
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, resize_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);  // vsync
    gl3w_init();

    const GLchar *vert_shader =
        "#version 330\n"
        "layout(location = 0) in vec2 point;\n"
        "uniform mat4 matrix;\n"
        "void main() {\n"
        "    gl_Position = matrix * vec4(point, 0.0, 1.0);\n"
        "}\n";
    const GLchar *frag_shader =
        "#version 330\n"
        "out vec4 color;\n"
        "void main() {\n"
        "    color = vec4(0.9, 0.9, 0.9, 0);\n"
        "}\n";

    GLuint shader = shader_program_new(vert_shader, frag_shader);

    while (glfwWindowShouldClose(window) != GLFW_TRUE) {
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        SCM shape_scm = scm_c_eval_string("(get-root-shape)");
        struct shape shape = scm_to_shape(shape_scm);
        draw(shape, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwTerminate();
}
