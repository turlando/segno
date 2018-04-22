#ifndef __SEGNO_TRANSFORMATION_SCM_H__
#define __SEGNO_TRANSFORMATION_SCM_H__

#include <stdbool.h>
#include <libguile.h>
#include <transformation.h>

SCM transformation_scm_t;

void transformation_scm_t_init();
bool transformation_scm_is_p(SCM obj_scm);
SCM transformation_to_scm(struct transformation transformation);
struct transformation scm_to_transformation(SCM transformation_scm);
struct transformations scm_to_transformations(SCM ts_scm);

#endif // __SEGNO_TRANSFORMATION_SCM_H__
