#ifndef _CUBEMAP_H_
#define _CUBEMAP_H_

#include "../gfx/vao.h"
#include "../gfx/vbo.h"
#include "../gfx/texture.h"
#include "../gfx/shader.h"
#include "stb_image.h"

typedef struct {
    texture_t tex;
    vao_t vao;
    vbo_t vbo;
    shader_t shd;
} cubemap_t;

GLuint cubemap_load(const char *faces[6]);

cubemap_t cubemap_create();

#endif
