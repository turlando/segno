#include <linmath.h>
#include <mutations.h>
#include <mutation.h>

struct mutation mutation_scale(double ratio) {
    struct mutation mutation;
    mat4x4 identity;
    mat4x4_identity(identity);
    mat4x4_scale_aniso(mutation.matrix, identity, ratio, ratio, ratio);
    return mutation;
}
