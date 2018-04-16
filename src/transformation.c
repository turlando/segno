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

mat4x4 *(*transformations_table[])(float) = {
    &identity_new,    // 0
    &translate_x_new, // 1
    &translate_y_new  // 2
};

struct transformation transformation(enum transformations transformation_type,
                                     float value) {
    struct transformation transformation = {
        .transformation = transformation_type,
        .value = value
    };
    return transformation;
}

mat4x4 *transformation_to_mat4x4(struct transformation transformation) {
    mat4x4 *mat = transformations_table[transformation.transformation](transformation.value);
    return mat;
}
