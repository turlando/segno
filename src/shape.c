#include <linmath.h>
#include <libguile.h>
#include <shape.h>

SCM shape_to_scm(struct shape shape) {
    size_t size = sizeof(struct shape);
    struct shape *shape_in_heap = scm_gc_malloc_pointerless(size, "shape");

    memcpy(shape_in_heap, &shape, size);
    return scm_from_pointer(shape_in_heap, NULL);
}

struct shape scm_to_shape(SCM shape_scm) {
    struct shape *shape_ref = scm_to_pointer(shape_scm);
    struct shape shape = *shape_ref;
    return shape;
}
