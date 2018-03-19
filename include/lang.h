#ifndef __SEGNO_LANG_H__
#define __SEGNO_LANG_H__

SCM lang_polygon(SCM n_scm);
SCM lang_scale(SCM ration_scm);
SCM lang_combine(SCM mutations_scm);
SCM lang_transform(SCM shape_scm, SCM transform_scm);
void lang_init();

#endif // __SEGNO_LANG_H__
