#include <string.h>
#include <stdlib.h>
#include <libguile.h>

#include <repl.h>
#include <segno.h>

static void init_readline() {
    scm_c_eval_string("(use-modules (ice-9 readline))");
    scm_c_eval_string("(activate-readline)");
}

static void init_server(int port) {
    char fmt[] =
        "(run-server"
        " (make-tcp-server-socket"
        "  #:host #f"
        "  #:addr INADDR_LOOPBACK"
        "  #:port %d))";
    size_t size = snprintf(NULL, 0, fmt, port) + 1;
    char *form = malloc(size);
    snprintf(form, size, fmt, port);

    scm_c_eval_string("(use-modules (system repl server))");
    scm_c_eval_string(form);

    free(form);
}

static void init_lang() {
    scm_c_define_gsubr("polygon",     1, 0, 1, &shape_polygon);

    scm_c_define_gsubr("scale",       0, 0, 1, &transform_scale);
    scm_c_define_gsubr("translate-x", 0, 0, 1, &transform_translate_x);
    scm_c_define_gsubr("translate-y", 0, 0, 1, &transform_translate_y);
    scm_c_define_gsubr("rotate",      0, 0, 1, &transform_rotate);

    scm_c_define_gsubr("fill",        0, 1, 0, &shape_fill);

    scm_c_define_gsubr("transform",   1, 0, 1, &shape_transform);
    scm_c_define_gsubr("combine",     0, 0, 1, &transform_combine);

    scm_c_primitive_load("init.scm");
}

void *repl_loop(void *a) {
    (void) a;

    scm_init_guile();
    init_readline();
    init_lang();
    scm_shell(0, NULL);

    return NULL;
}

void *repl_server_loop(void *a) {
    struct repl_args *args = (struct repl_args *) a;

    scm_init_guile();
    init_lang();
    init_server(args->repl_server_port);

    return NULL;
}
