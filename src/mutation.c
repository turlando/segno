#include <libguile.h>
#include <mutation.h>

SCM mutation_to_scm(struct mutation mutation) {
    size_t size = sizeof(struct mutation);
    struct mutation *mutation_in_heap = scm_gc_malloc_pointerless(size, "mutation");

    memcpy(mutation_in_heap, &mutation, size);
    return scm_from_pointer(mutation_in_heap, NULL);
}

struct mutation scm_to_mutation(SCM mutation_scm) {
    struct mutation *mutation_ref = scm_to_pointer(mutation_scm);
    struct mutation mutation = *mutation_ref;
    return mutation;
}

struct mutation mutation_combine_two(struct mutation one, struct mutation two) {
    struct mutation mutation;
    mat4x4_mul(mutation.matrix, one.matrix, two.matrix);
    return mutation;
}
