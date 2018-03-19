#ifndef __SEGNO_MUTATIONS_H__
#define __SEGNO_MUTATIONS_H__

struct mutation mutation_translate_x(double x);
struct mutation mutation_translate_y(double y);
struct mutation mutation_scale(double ratio);
struct mutation mutation_rotate(double turns);

#endif // __SEGNO_MUTATIONS_H__
