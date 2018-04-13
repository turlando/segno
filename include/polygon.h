#ifndef __SEGNO_POLYGON_H__
#define __SEGNO_POLYGON_H__

#include <stdbool.h>
#include <linmath.h>

struct polygon {
    unsigned int sides;
    bool fill;
    mat4x4 transformation;
};

struct polygon polygon(int sides, bool fill);
SCM polygon_to_scm(struct polygon polygon);
struct polygon scm_to_polygon(SCM polygon_scm);
float *polygon_vertices_new(int n);
size_t polygon_vertices_size(int n);

#endif // __SEGNO_POLYGON_H__
