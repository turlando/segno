#include <string.h>
#include <stdlib.h>
#include <libguile.h>
#include <repl.h>
#include <lang.h>

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

void *repl_loop(void *a) {
    (void) a;

    scm_init_guile();
    init_readline();
    lang_bind_primitives();
    scm_shell(0, NULL);

    return NULL;
}

void *repl_server_loop(void *a) {
    struct repl_args *args = (struct repl_args *) a;

    scm_init_guile();
    lang_bind_primitives();
    init_server(args->repl_server_port);

    return NULL;
}
