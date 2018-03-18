#include <segno.h>
#include <repl.h>

int main() {
    scm_init_guile();

    pthread_t repl_thread;
    pthread_create(&repl_thread, NULL, repl_loop, NULL);

    Context context = gl_init();

    gl_loop(context);
    gl_clean(context);
    return 0;
}
