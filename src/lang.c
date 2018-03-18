#include <libguile.h>
#include <lang.h>
#include <utils.h>
#include <shape.h>
#include <mutation.h>
#include <mutations.h>

SCM lang_polygon(SCM n_scm) {
    int n = scm_to_int(n_scm);
    struct shape shape = shape_polygon(n);
    SCM shape_scm = shape_to_scm(shape);
    return shape_scm;
}

SCM lang_scale(SCM ratio_scm) {
    double ratio = scm_to_double(ratio_scm);
    struct mutation mutation = mutation_scale(ratio);
    SCM mutation_scm = mutation_to_scm(mutation);
    return mutation_scm;
}

SCM lang_combine(SCM mutations_scm) {
    SCM source_scm;
    struct mutation dest;

    foreach (source_scm, mutations_scm) {
        struct mutation source = scm_to_mutation(source_scm);
        dest = mutation_combine_two(dest, source);
    }

    SCM dest_scm = mutation_to_scm(dest);
    return dest_scm;
}

SCM lang_transform(SCM shape_scm, SCM mutation_scm) {
    struct shape shape = scm_to_shape(shape_scm);
    struct mutation mutation = scm_to_mutation(mutation_scm);
    struct shape new_shape = shape_mutation_apply(shape, mutation);
    SCM new_shape_scm = shape_to_scm(new_shape);
    return new_shape_scm;
}

void lang_bind_primitives() {
    scm_c_define_gsubr("polygon",     1, 0, 0, &lang_polygon);
    scm_c_define_gsubr("transform",   2, 0, 0, &lang_transform);
    scm_c_define_gsubr("combine",     0, 0, 1, &lang_combine);
    scm_c_define_gsubr("scale",       1, 0, 0, &lang_scale);
    scm_c_primitive_load("init.scm");
}
