#pragma once
#include <stdbool.h>
#include <math.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <libguile.h>
#include <linmath.h>

#define M_PI 3.141592653589793


#define is_pair scm_is_pair
#define first   scm_car
#define rest    scm_cdr
#define cons    scm_cons

#define foreach(x, xs) \
    for(; \
        x = is_pair(xs) ? first(xs) : SCM_UNDEFINED, is_pair(xs); \
        xs = rest(xs))


typedef struct {
    int n;
    GLuint vertex_buffer;
    GLuint vertex_array;
    mat4x4 matrix;

    bool fill;
} Shape;


typedef struct {
    mat4x4 matrix;
} Transform;


// shapes.c
SCM scm_from_shape(Shape shape);
Shape scm_to_shape(SCM shape_scm);

SCM shape_transform(SCM shape, SCM transform);
SCM shape_polygon(SCM n_scm, SCM changes);
SCM shape_fill(SCM shape_scm);

// transformations.c
SCM transform_apply(SCM shape, SCM transform);

SCM scm_from_transform(Transform transform);
Transform scm_to_transform(SCM transform_scm);

SCM transform_map(SCM transform, SCM in_shapes);
SCM transform_apply(SCM shape, SCM transform);
SCM transform_combine(SCM transforms);

SCM transform_rotate(SCM values);
SCM transform_translate_x(SCM values);
SCM transform_translate_y(SCM values);
SCM transform_scale(SCM values);


// global variables (TODO: do not use them)
GLFWwindow *global_window;
