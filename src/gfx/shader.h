#ifndef _SHADER_H_
#define _SHADER_H_

#include "gfx.h"
#include <cglm/struct.h>

struct Shader {
    GLuint handle, vs_handle, fs_handle;
};

struct Shader shader_create(const char *vs_path, const char *fs_path);
void shader_destroy(struct Shader self);
void shader_bind(struct Shader self);

void shader_uniform_int(struct Shader self, const char *name, int v);
void shader_uniform_mat4(struct Shader self, const char *name, mat4 *m);

#endif
