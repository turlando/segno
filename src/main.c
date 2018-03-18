#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <libguile.h>
#define OPTPARSE_IMPLEMENTATION
#include <optparse.h>
#include <repl.h>
#include <window.h>

static void print_help(FILE *fp, char *name) {
    char help_string[] =
        "Usage %s: [-h] [-l]\n"
        "\n"
        "optional arguments:\n"
        "  -h, --help            show this help message and exit\n"
        "  -l, --listen PORT     spawn a REPL server (e.g.: -l 1337)\n";

    fprintf(fp, help_string, name);
}

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
        print_help(stderr, argv[0]);
        fprintf(stderr, "\nError: %s\n", opt_failure_msg);
        exit(EXIT_FAILURE);
    }

    if (want_help == true) {
        print_help(stdout, argv[0]);
        exit(EXIT_SUCCESS);
    }

    // FIXME: apparently can't be removed because of globals fuckeries
    scm_init_guile();

    // FIXME: there is a race condition bewteen the REPL and the shader
    // guile: uncaught throw to unbound-variable: (#f Unbound variable: ~S (get-root-shape) #f)
    // Doesn't seem to happen with the network server
    pthread_t repl_thread;
    if (want_repl_server == true) {
        struct repl_args a = {
            .repl_server_port = repl_server_port
        };
        pthread_create(&repl_thread, NULL, repl_server_loop, &a);
    } else {
        pthread_create(&repl_thread, NULL, repl_loop, NULL);
    }

    window_loop();

    return 0;
}
