#include <stdbool.h>
#include <libguile.h>
#include <polygon_scm.h>
#include <polygon.h>

void polygon_scm_t_init() {
    SCM name = scm_string_to_symbol(scm_from_utf8_string("polygon"));
    SCM slots = scm_list_1(scm_string_to_symbol(scm_from_utf8_string("data")));
    polygon_scm_t = scm_make_foreign_object_type(name, slots, NULL);
}

bool polygon_scm_is_p(SCM obj_scm) {
    return SCM_IS_A_P(obj_scm, polygon_scm_t) ? true : false;
}

SCM polygon_to_scm(struct polygon polygon) {
    size_t size = sizeof(struct polygon);
    struct polygon *polygon_ref = scm_gc_malloc_pointerless(size, "polygon");
    memcpy(polygon_ref, &polygon, size);
    return scm_make_foreign_object_1(polygon_scm_t, polygon_ref);
}

struct polygon scm_to_polygon(SCM polygon_scm) {
    scm_assert_foreign_object_type(polygon_scm_t, polygon_scm);
    struct polygon *polygon_ref = scm_foreign_object_ref(polygon_scm, 0);
    struct polygon polygon = *polygon_ref;
    return polygon;
}
