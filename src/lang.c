#include <stdbool.h>
#include <libguile.h>
#include <lang.h>
#include <utils.h>
#include <polygon.h>
#include <shape.h>
#include <transformation.h>

static void init_polygon_type() {
    SCM name = scm_string_to_symbol(scm_from_utf8_string("polygon"));
    SCM slots = scm_list_1(scm_string_to_symbol(scm_from_utf8_string("data")));
    lang_polygon_type = scm_make_foreign_object_type(name, slots, NULL);
}

static SCM polygon_to_scm(struct polygon polygon) {
    size_t size = sizeof(struct polygon);
    struct polygon *polygon_ref = scm_gc_malloc_pointerless(size, "polygon");
    memcpy(polygon_ref, &polygon, size);
    return scm_make_foreign_object_1(lang_polygon_type, polygon_ref);
}

static struct polygon scm_to_polygon(SCM polygon_scm) {
    scm_assert_foreign_object_type(lang_polygon_type, polygon_scm);
    struct polygon *polygon_ref = scm_foreign_object_ref(polygon_scm, 0);
    struct polygon polygon = *polygon_ref;
    return polygon;
}

static SCM scm_polygon(SCM sides_scm, SCM fill_scm) {
    int sides = scm_to_int(sides_scm);
    bool fill = scm_to_bool(fill_scm);

    struct polygon polygon_c = polygon(sides, fill);
    SCM polygon_scm = polygon_to_scm(polygon_c);

    return polygon_scm;
}

static void init_transformation_type() {
    SCM name = scm_string_to_symbol(scm_from_utf8_string("transformation"));
    SCM slots = scm_list_1(scm_string_to_symbol(scm_from_utf8_string("data")));
    lang_transformation_type = scm_make_foreign_object_type(name, slots, NULL);
}

static SCM transformation_to_scm(struct transformation transformation) {
    size_t size = sizeof(struct transformation);
    struct transformation *transformation_ref = scm_gc_malloc_pointerless(size, "transformation");
    memcpy(transformation_ref, &transformation, size);
    return scm_make_foreign_object_1(lang_transformation_type, transformation_ref);
}

static SCM scm_translate_x(SCM value_scm) {
    float value = (float) scm_to_double(value_scm);

    struct transformation transformation_c = transformation(TRANSFORMATION_TRANSLATE_X, value);
    SCM transformation_scm = transformation_to_scm(transformation_c);

    return transformation_scm;
}

static void bind_primitives() {
    scm_c_define_gsubr("polygon",     2, 0, 0, &scm_polygon);
    scm_c_define_gsubr("translate-x", 1, 0, 0, &scm_translate_x);
}

static void bind_draw() {
    const char bind_draw[] =
        "(use-modules (ice-9 threads))"
        "(define root-object '(polygon 4 #f))"
        "(define root-mutex  (make-mutex))"
        "(define (get-root-object) (with-mutex root-mutex"
        "                           (eval root-object"
        "                            (interaction-environment))))"
        "(define-macro (draw body) (with-mutex root-mutex"
        "                           (set! root-object body)) #t)";
    scm_c_eval_string(bind_draw);
}

void lang_init() {
    init_polygon_type();
    init_transformation_type();
    bind_primitives();
    bind_draw();
}

SCM lang_get_root_object() {
    return scm_c_eval_string("(get-root-object)");
}

struct shape lang_object_to_shape(SCM object_scm) {
    struct polygon polygon = scm_to_polygon(object_scm);
    struct shape shape = polygon_to_shape(polygon);
    return shape;
}
