#ifndef _CHUNK_H_
#define _CHUNK_H_

#define CHUNK_X 32
#define CHUNK_Y 256
#define CHUNK_Z 32

#include <stdbool.h>
#include "../gfx/vao.h"
#include "../gfx/vbo.h"

typedef struct {
    bool blocks[CHUNK_X][CHUNK_Y][CHUNK_Z];
    vao_t vao;
    vbo_t vbo;
    int num_vertices;
} chunk_t;

void chunk_render(chunk_t *self);
void chunk_create(chunk_t *self);

#endif
