#include <linmath.h>
#include <mutations.h>
#include <mutation.h>
#include <utils.h>

struct mutation mutation_translate_x(double x) {
    struct mutation mutation;
    mat4x4_translate(mutation.matrix, x, 0, 0);
    return mutation;
 }

struct mutation mutation_translate_y(double y) {
    struct mutation mutation;
    mat4x4_translate(mutation.matrix, 0, y, 0);
    return mutation;
}

struct mutation mutation_scale(double ratio) {
    struct mutation mutation;
    mat4x4 identity;
    mat4x4_identity(identity);
    mat4x4_scale_aniso(mutation.matrix, identity, ratio, ratio, ratio);
    return mutation;
}

struct mutation mutation_rotate(double turns) {
    struct mutation mutation;
    mat4x4 identity;
    mat4x4_identity(identity);
    mat4x4_rotate_Z(mutation.matrix, identity, turns * (2 * M_PI));
    return mutation;
}
