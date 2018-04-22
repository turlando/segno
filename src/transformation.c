#include <string.h>
#include <stdlib.h>
#include <linmath.h>
#include <transformation.h>

static mat4x4 *identity_new(float value) {
    (void) value;
    mat4x4 *mat = malloc(sizeof(mat4x4));
    mat4x4_identity(*mat);
    return mat;
}

static mat4x4 *translate_x_new(float value) {
    mat4x4 *mat = malloc(sizeof(mat4x4));
    mat4x4_translate(*mat, value, 0, 0);
    return mat;
}

static mat4x4 *translate_y_new(float value) {
    mat4x4 *mat = malloc(sizeof(mat4x4));
    mat4x4_translate(*mat, 0, value, 0);
    return mat;
}

static mat4x4 *scale_new(float value) {
    mat4x4 identity;
    mat4x4_identity(identity);

    mat4x4 *mat = malloc(sizeof(mat4x4));
    mat4x4_scale_aniso(*mat, identity, value, value, value);

    return mat;
}

static mat4x4 *(*transformations_table[])(float) = {
    &identity_new,    // 0
    &translate_x_new, // 1
    &translate_y_new, // 2
    &scale_new        // 3
};

struct transformation transformation(enum transformation_type type,
                                     float value) {
    struct transformation transformation = {
        .transformation = type,
        .value = value
    };
    return transformation;
}

mat4x4 *transformation_to_mat4x4(struct transformation t) {
    mat4x4 *mat = transformations_table[t.transformation](t.value);
    return mat;
}

mat4x4 *transformations_to_mat4x4(struct transformations ts) {
    mat4x4 *out = malloc(sizeof(mat4x4));
    mat4x4_identity(*out);

    struct transformation t;
    mat4x4 *m;
    for (size_t i = 0; i < ts.count; i++) {
        t = ts.ts[i];
        m = transformation_to_mat4x4(t);
        mat4x4_mul(*out, *m, *out);
    }

    return out;
}
