#ifndef __SEGNO_POLYGON_SCM_H__
#define __SEGNO_POLYGON_SCM_H__

#include <libguile.h>
#include <polygon.h>

SCM polygon_scm_t;

void polygon_scm_t_init();
bool polygon_scm_is_p(SCM obj_scm);
SCM polygon_to_scm(struct polygon polygon);
struct polygon scm_to_polygon(SCM polygon_scm);

#endif // __SEGNO_POLYGON_SCM_H__
