#include <segno.h>
#include <repl.h>
#include <window.h>

int main() {
    scm_init_guile();

    pthread_t repl_thread;
    pthread_create(&repl_thread, NULL, repl_loop, NULL);

    window_loop();

    return 0;
}
