#ifndef _SHADER_H_
#define _SHADER_H_

#include "gfx.h"

struct Shader {
    GLuint handle, vs_handle, fs_handle;
};

struct Shader shader_create(const char *vs_path, const char *fs_path);

#endif
