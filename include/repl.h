#ifndef __SEGNO_REPL_H__
#define __SEGNO_REPL_H__

struct repl_args {
    int repl_server_port;
};

void *repl_loop(void *v);
void *repl_server_loop(void *a);

#endif // __SEGNO_REPL_H__
