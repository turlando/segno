#include <stdbool.h>
#include <libguile.h>
#include <lang.h>
#include <utils.h>
#include <polygon.h>

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
    bind_primitives();
    bind_draw();
}
