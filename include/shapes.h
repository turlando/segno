#pragma once

#include <libguile.h>
#include <shader.h>

void shape_draw(SCM shape, struct shader_program program);
