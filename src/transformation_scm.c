#include <libguile.h>
#include <transformation_scm.h>
#include <transformation.h>
#include <utils.h>

void transformation_scm_t_init() {
    SCM name = scm_from_utf8_symbol("transformation");
    SCM slots = scm_list_1(scm_string_to_symbol(scm_from_utf8_string("data")));
    transformation_scm_t = scm_make_foreign_object_type(name, slots, NULL);
}

bool transformation_scm_is_p(SCM obj_scm) {
    return SCM_IS_A_P(obj_scm, transformation_scm_t) ? true : false;
}

SCM transformation_to_scm(struct transformation transformation) {
    size_t size = sizeof(struct transformation);
    struct transformation *transformation_ref =
        scm_gc_malloc_pointerless(size, "transformation");
    memcpy(transformation_ref, &transformation, size);
    return scm_make_foreign_object_1(transformation_scm_t, transformation_ref);
}

struct transformation scm_to_transformation(SCM transformation_scm) {
    scm_assert_foreign_object_type(transformation_scm_t, transformation_scm);
    struct transformation *transformation_ref =
        scm_foreign_object_ref(transformation_scm, 0);
    struct transformation transformation = *transformation_ref;
    return transformation;
}

struct transformations scm_to_transformations(SCM ts_scm) {
    SCM count_scm = scm_length(ts_scm);
    size_t count = scm_to_uint(count_scm);

    struct transformations ts;
    ts.count = count;
    ts.ts = malloc(sizeof(struct transformations) * ts.count);

    size_t i = 0;
    SCM t_scm;
    FOR_SCM(t_scm, ts_scm) {
        ts.ts[i] = scm_to_transformation(t_scm);
        i++;
    }

    return ts;
}
