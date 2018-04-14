#include <stdbool.h>
#include <libguile.h>
#include <lang.h>
#include <utils.h>
#include <polygon.h>

SCM polygon_to_scm(struct polygon polygon) {
    size_t size = sizeof(struct polygon);
    struct polygon *polygon_scm = scm_gc_malloc_pointerless(size, "polygon");
    memcpy(polygon_scm, &polygon, size);
    return scm_make_foreign_object_1(lang_polygon_type, polygon_scm);
}

struct polygon scm_to_polygon(SCM polygon_scm) {
    struct polygon *polygon_ref = scm_foreign_object_ref(polygon_scm, 0);
    struct polygon polygon = *polygon_ref;
    return polygon;
}

static void init_polygon_type() {
    SCM name = scm_string_to_symbol(scm_from_utf8_string("polygon"));
    SCM slots = scm_list_1(scm_string_to_symbol(scm_from_utf8_string("data")));
    lang_polygon_type = scm_make_foreign_object_type(name, slots, NULL);
}

static SCM scm_polygon(SCM sides_scm, SCM fill_scm) {
    int sides = scm_to_int(sides_scm);
    bool fill = scm_to_bool(fill_scm);

    struct polygon polygon_c = polygon(sides, fill);
    SCM polygon_scm = polygon_to_scm(polygon_c);

    return polygon_scm;
}

static void bind_primitives() {
    scm_c_define_gsubr("polygon", 2, 0, 0, &scm_polygon);
}

static void bind_draw() {
    const char bind_draw[] =
        "(use-modules (ice-9 threads))"
        "(define root-shape '(polygon 4 #f))"
        "(define mutex      (make-mutex))"
        "(define (get-root-shape) (with-mutex mutex"
        "                          (eval root-shape"
        "                           (interaction-environment))))"
        "(define-macro (draw body) (with-mutex mutex (set! root-shape body)) #t)";
    scm_c_eval_string(bind_draw);
}

void lang_init() {
    init_polygon_type();
    bind_primitives();
    bind_draw();
}
