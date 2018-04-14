#ifndef __SEGNO_LANG_H__
#define __SEGNO_LANG_H__

#include <libguile.h>
#include <polygon.h>

SCM lang_polygon_type;

SCM polygon_to_scm(struct polygon polygon);
struct polygon scm_to_polygon(SCM polygon_scm);
void lang_init();

#endif // __SEGNO_LANG_H__
