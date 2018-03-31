#include <libguile.h>
#include <lang.h>
#include <utils.h>
#include <shapes.h>

static SCM polygon(SCM n_scm) {
    int n = scm_to_int(n_scm);
    struct shape shape = shape_polygon(n);
    SCM shape_scm = shape_to_scm(shape);
    return shape_scm;
}

static void bind_primitives() {
    scm_c_define_gsubr("polygon", 1, 0, 0, &polygon);
}

static void bind_draw() {
    const char bind_draw[] =
        "(use-modules (ice-9 threads))"
        "(define root-shape '(polygon 4))"
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
