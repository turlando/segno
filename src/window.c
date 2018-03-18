#include <segno.h>
#include <utils.h>

static void gl_init() {
    if (glfwInit() != GLFW_TRUE) {
        fprintf(stderr, "GLFW3: initialization failed\n");
        exit(EXIT_FAILURE);
    }
}

static void gl_window_init() {
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

static GLFWwindow *window_new(int w, int h, const char *title) {
    GLFWwindow *window = glfwCreateWindow(w, h, title, NULL, NULL);
    global_window = window;

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // vsync

    // TODO: if multiple windows use a static flag to call this just once
    if (gl3wInit()) {
        fprintf(stderr, "gl3w: failed to initialize\n");
        exit(EXIT_FAILURE);
    }

    return window;
}

static Program shader_new() {
    /* Shader sources */
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

    Program program = program_new(vert_shader, frag_shader);
    return program;
}

static void gl_clean(Program program) {
    program_free(program);
    glfwTerminate();
}

static void size_callback(GLFWwindow* window, int width, int height) {
    (void) window;
    int side = MAX(width, height);
    int x0 = (width - side) / 2;
    int y0 = (height - side) / 2;

    glViewport(x0, y0, side, side);
}

static void key_callback(GLFWwindow *window,
                         int key, int scancode, int action, int mods) {
    (void) scancode;
    (void) mods;
    if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

static void gl_loop(GLFWwindow *window, Program shader) {
    glfwSetWindowSizeCallback(window, size_callback);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        SCM shape_scm = scm_c_eval_string("(get-root-shape)");
        shape_draw(shape_scm, shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void window_loop() {
    gl_init();
    gl_window_init();

    GLFWwindow *window = window_new(640, 640, "Segno");
    Program shader = shader_new();

    gl_loop(window, shader);

    gl_clean(shader);
}
