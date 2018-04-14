#include <transformation.h>

struct transformation transformation(enum transformations transformation_type,
                                     float value) {
    struct transformation transformation = {
        .transformation = transformation_type,
        .value = value
    };
    return transformation;
}
