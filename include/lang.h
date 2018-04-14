#ifndef __SEGNO_LANG_H__
#define __SEGNO_LANG_H__

#include <libguile.h>

SCM lang_polygon_type;
SCM lang_transformation_type;

void lang_init();
SCM lang_get_root_object();
struct shape lang_polygon_to_shape(SCM polygon_scm);

#endif // __SEGNO_LANG_H__
