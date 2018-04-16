#include <stdbool.h>
#include <libguile.h>
#include <lang.h>
#include <utils.h>
#include <polygon.h>
#include <polygon_scm.h>
#include <transformation.h>
#include <transformation_scm.h>
#include <shape.h>

static SCM scm_polygon(SCM sides_scm, SCM fill_scm) {
    int sides = scm_to_int(sides_scm);
    bool fill = scm_to_bool(fill_scm);

    struct polygon polygon_c = polygon(sides, fill);
    SCM polygon_scm = polygon_to_scm(polygon_c);

    return polygon_scm;
}

static SCM scm_transform(SCM polygon_scm, SCM transformation_scm) {
    if (polygon_scm_is_p(polygon_scm) == false)
        return scm_error_scm(polygon_scm, SCM_BOOL_F, NULL, NULL, SCM_BOOL_F);

    if (transformation_scm_is_p(transformation_scm) == false)
        return scm_error_scm(transformation_scm, SCM_BOOL_F, NULL, NULL, SCM_BOOL_F);

    return scm_cons(polygon_scm, transformation_scm);
}

static SCM scm_translate_x(SCM value_scm) {
    float value = (float) scm_to_double(value_scm);

    struct transformation transformation_c = transformation(TRANSFORMATION_TRANSLATE_X, value);
    SCM transformation_scm = transformation_to_scm(transformation_c);

    return transformation_scm;
}

static SCM scm_translate_y(SCM value_scm) {
    float value = (float) scm_to_double(value_scm);

    struct transformation transformation_c = transformation(TRANSFORMATION_TRANSLATE_Y, value);
    SCM transformation_scm = transformation_to_scm(transformation_c);

    return transformation_scm;
}

static void bind_primitives() {
    scm_c_define_gsubr("polygon",     2, 0, 0, &scm_polygon);
    scm_c_define_gsubr("transform",   2, 0, 0, &scm_transform);
    scm_c_define_gsubr("translate-x", 1, 0, 0, &scm_translate_x);
    scm_c_define_gsubr("translate-y", 1, 0, 0, &scm_translate_y);
}

static void bind_draw() {
    const char draw[] =
        "(use-modules (ice-9 threads))"
        "(define root-object '(polygon 4 #f))"
        "(define root-mutex  (make-mutex))"
        "(define (get-root-object) (with-mutex root-mutex"
        "                           (eval root-object"
        "                            (interaction-environment))))"
        "(define-macro (draw body) (with-mutex root-mutex"
        "                           (set! root-object body)) #t)";
    scm_c_eval_string(draw);
}

void lang_init() {
    polygon_scm_t_init();
    transformation_scm_t_init();
    bind_primitives();
    bind_draw();
}

SCM lang_get_root_object() {
    return scm_c_eval_string("(get-root-object)");
}

struct shape lang_object_to_shape(SCM object_scm) {
    // If it gets out of a (transform ...) form
    if (scm_is_pair(object_scm) == true) {
        SCM polygon_scm = scm_car(object_scm);
        SCM transformation_scm = scm_cdr(object_scm);
        struct polygon polygon = scm_to_polygon(polygon_scm);
        struct transformation transformation = scm_to_transformation(transformation_scm);
        struct shape shape = transform_to_shape(polygon, transformation);
        return shape;
    }

    // If it gets out of a (polygon ...) form
    struct polygon polygon = scm_to_polygon(object_scm);
    struct shape shape = polygon_to_shape(polygon);
    return shape;
}
