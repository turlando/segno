#pragma once

struct repl_args {
    int repl_server_port;
};

void *repl_loop(void *v);
void *repl_server_loop(void *a);
