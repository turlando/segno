#ifndef __SEGNO_TRANSFORMATION_H__
#define __SEGNO_TRANSFORMATION_H__

#include <linmath.h>

enum transformation_type {
    TRANSFORMATION_IDENTITY    = 0,
    TRANSFORMATION_TRANSLATE_X = 1,
    TRANSFORMATION_TRANSLATE_Y = 2,
    TRANSFORMATION_SCALE       = 3,
    TRANSFORMATION_ROTATE      = 4
};

struct transformation {
    enum transformation_type transformation;
    float value;
};

struct transformations {
    size_t count;
    struct transformation *ts;
};

struct transformation transformation(enum transformation_type transformation_type,
                                     float value);
mat4x4 *transformation_to_mat4x4(struct transformation transformation);
mat4x4 *transformations_to_mat4x4(struct transformations ts);

#endif // __SEGNO_TRANSFORMATION_H__
