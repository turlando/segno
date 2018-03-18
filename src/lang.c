#include <libguile.h>
#include <shape.h>

SCM lang_polygon(SCM n_scm) {
    int n = scm_to_int(n_scm);
    struct shape shape = shape_polygon(n);
    SCM shape_scm = shape_to_scm(shape);
    return shape_scm;
}
