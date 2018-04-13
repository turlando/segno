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

static GLFWwindow *window_main_new() {
    GLFWwindow *window = window_new(640, 640, "Segno");
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, resize_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSwapInterval(1);  // vsync
    return window;
}

void window_loop() {
    glfw_init();

    glfw_window_init();
    GLFWwindow *window = window_main_new();

    gl3w_init();
    GLuint shader = shader_program_new(shape_vertex_shader,
                                       shape_fragment_shader);

    while (glfwWindowShouldClose(window) != GLFW_TRUE) {
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        SCM polygon_scm = scm_c_eval_string("(get-root-shape)");
        struct polygon polygon = scm_to_polygon(polygon_scm);
        struct shape shape = polygon_to_shape(polygon);

        shape_draw(shader, shape);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);
    glfwDestroyWindow(window);
    glfwTerminate();
}
