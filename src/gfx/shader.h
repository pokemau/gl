#ifndef _SHADER_H_
#define _SHADER_H_

#include "gfx.h"
#include <cglm/struct.h>

typedef struct {
    GLuint handle, vs_handle, fs_handle;
} shader_t;

shader_t shader_create(const char *vs_path, const char *fs_path);
void shader_destroy(shader_t self);
void shader_bind(shader_t self);

void shader_uniform_int(shader_t self, const char *name, int v);
void shader_uniform_mat4(shader_t self, const char *name, mat4 *m);

#endif
