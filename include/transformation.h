#ifndef __SEGNO_TRANSFORMATION_H__
#define __SEGNO_TRANSFORMATION_H__

enum transformations {
    TRANSFORMATION_IDENTITY    = 0,
    TRANSFORMATION_TRANSLATE_X = 1,
    TRANSFORMATION_TRANSLATE_Y = 2
};

struct transformation {
    enum transformations transformation;
    float value;
};

struct transformation transformation(enum transformations transformation_type,
                                     float value);

#endif // __SEGNO_TRANSFORMATION_H__
