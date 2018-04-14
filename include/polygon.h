#ifndef __SEGNO_POLYGON_H__
#define __SEGNO_POLYGON_H__

#include <stdbool.h>
#include <linmath.h>

struct polygon {
    unsigned int sides;
    bool fill;
};

struct polygon polygon(int sides, bool fill);
float *polygon_vertices_new(int n);
size_t polygon_vertices_size(int n);

#endif // __SEGNO_POLYGON_H__
