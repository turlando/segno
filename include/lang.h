#ifndef __SEGNO_LANG_H__
#define __SEGNO_LANG_H__

#include <libguile.h>

void lang_init();
SCM lang_get_root_object();
struct shapes lang_object_to_shapes(SCM polygon_scm);

#endif // __SEGNO_LANG_H__
