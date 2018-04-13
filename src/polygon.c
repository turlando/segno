#include <stdlib.h>
#include <math.h>
#include <linmath.h>
#include <libguile.h>
#include <utils.h>
#include <polygon.h>

struct polygon polygon(int sides, bool fill) {
    struct polygon polygon = {
        .sides = sides,
        .fill = fill
    };
    return polygon;
}

SCM polygon_to_scm(struct polygon polygon) {
    size_t size = sizeof(struct polygon);
    struct polygon *polygon_ref = scm_gc_malloc_pointerless(size, "polygon");
    memcpy(polygon_ref, &polygon, size);
    return scm_from_pointer(polygon_ref, NULL);
}

struct polygon scm_to_polygon(SCM polygon_scm) {
    struct polygon *polygon_ref = scm_to_pointer(polygon_scm);
    struct polygon polygon = *polygon_ref;
    return polygon;
}

/**
 * Return an array of size (n * 2) storing the coordinates (x, y)
 * of the vertices of a regular polygon with (n) sides.
 * The pointer should passed to free(3) when it is no longer needed.
 */
float *polygon_vertices_new(int sides) {
    float *array = malloc(sizeof(float) * sides * 2);

    int i;
    float t;

    for (i = 0; i < sides; i++) {
        t = i * (2 * M_PI / sides) + (M_PI / 2);

        array[i * 2]    = cos(t);
        array[i * 2 +1] = sin(t);
    }

    return array;
}

/**
 * Return the bytes required to allocate the array returned
 * by polygon_vertices_new(int n).
 */
size_t polygon_vertices_size(int sides) {
    return sizeof(float) * sides * 2;
}
