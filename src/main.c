#define OPTPARSE_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <libguile.h>
#include <optparse.h>
#include <repl.h>
#include <window.h>

const char help_fmt[] =
    "Usage %s: [-h] [-l]\n"
    "\n"
    "optional arguments:\n"
    "  -h, --help            show this help message and exit\n"
    "  -l, --listen PORT     spawn a REPL server (e.g.: -l 1337)\n";

int main(int argc, char **argv) {
    (void) argc;

    struct optparse_long longopts[] = {
        {"help",   'h', OPTPARSE_OPTIONAL},
        {"listen", 'l', OPTPARSE_REQUIRED},
        {NULL}
    };

    struct optparse options;
    optparse_init(&options, argv);

    bool opt_failure = false;
    char *opt_failure_msg = NULL;
    bool want_help = false;
    bool want_repl_server = false;
    int repl_server_port = 0;

    int option;
    while ((option = optparse_long(&options, longopts, NULL)) != -1) {
        switch (option) {
        case '?':
            opt_failure = true;
            opt_failure_msg = options.errmsg;
            break;
        case 'h':
            want_help = true;
            break;
        case 'l':
            want_repl_server = true;
            repl_server_port = atoi(options.optarg);
            break;
        }
    }

    if (opt_failure == true) {
        fprintf(stderr, "\nError: %s\n", opt_failure_msg);
        fprintf(stderr, help_fmt, argv[0]);
        exit(EXIT_FAILURE);
    }

    if (want_help == true) {
        fprintf(stdout, help_fmt, argv[0]);
        exit(EXIT_SUCCESS);
    }

    struct repl_args repl_args = {
        .want_server = want_repl_server,
        .server_port = repl_server_port
    };

    pthread_t repl_thread;
    scm_init_guile();
    pthread_create(&repl_thread, NULL, repl_loop, &repl_args);

    window_loop();

    pthread_join(repl_thread, NULL);

    return 0;
}
