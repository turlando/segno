#ifndef __SEGNO_REPL_H__
#define __SEGNO_REPL_H__

#include <stdbool.h>

struct repl_args {
    bool want_server;
    int server_port;
};

void *repl_loop(void *v);

#endif // __SEGNO_REPL_H__
