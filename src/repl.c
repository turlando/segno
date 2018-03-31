#include <string.h>
#include <stdlib.h>
#include <libguile.h>
#include <utils.h>
#include <repl.h>
#include <lang.h>

static void init_readline() {
    scm_c_eval_string("(use-modules (ice-9 readline))");
    scm_c_eval_string("(activate-readline)");
}

static void init_server(int port) {
    const char fmt[] =
        "(run-server"
        " (make-tcp-server-socket"
        "  #:host #f"
        "  #:addr INADDR_LOOPBACK"
        "  #:port %d))";
    char *form = vasnprintf(fmt, port);

    scm_c_eval_string("(use-modules (system repl server))");
    scm_c_eval_string(form);

    free(form);
}

void *repl_loop(void *a) {
    struct repl_args *args = (struct repl_args *) a;

    scm_init_guile();
    lang_init();

    if (args->want_server == false) {
        init_readline();
        scm_shell(0, NULL);
    } else {
        init_server(args->server_port);
    }

    return NULL;
}
