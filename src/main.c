#include <segno.h>


void *guile_repl(void *v) {
    (void) v;

    scm_init_guile();
    guile_bind_primitives();
    scm_c_eval_string("(use-modules (ice-9 readline))");
    scm_c_eval_string("(activate-readline)");
    scm_c_primitive_load("init.scm");

    scm_shell(0, NULL);

    return NULL;
}

void guile_bind_primitives() {
    scm_c_define_gsubr("polygon",     1, 0, 1, &shape_polygon);

    scm_c_define_gsubr("scale",       0, 0, 1, &transform_scale);
    scm_c_define_gsubr("translate-x", 0, 0, 1, &transform_translate_x);
    scm_c_define_gsubr("translate-y", 0, 0, 1, &transform_translate_y);
    scm_c_define_gsubr("rotate",      0, 0, 1, &transform_rotate);

    scm_c_define_gsubr("fill",        0, 1, 0, &shape_fill);

    scm_c_define_gsubr("transform",   1, 0, 1, &shape_transform);
    scm_c_define_gsubr("combine",     0, 0, 1, &transform_combine);
}

int main() {
    scm_init_guile();

    pthread_t repl_thread;
    pthread_create(&repl_thread, NULL, guile_repl, NULL);

    Context context = gl_init();

    gl_loop(context);
    gl_clean(context);
    return 0;
}
