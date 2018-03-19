#ifndef __SEGNO_MUTATION_H__
#define __SEGNO_MUTATION_H__

#include <linmath.h>
#include <libguile.h>

struct mutation {
    mat4x4 matrix;
};

SCM mutation_to_scm(struct mutation mutation);
struct mutation scm_to_mutation(SCM mutation_scm);
struct mutation mutation_combine_two(struct mutation one, struct mutation two);

#endif // __SEGNO_MUTATION_H__
