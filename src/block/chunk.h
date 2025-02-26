#ifndef _CHUNK_H_
#define _CHUNK_H_

#define CHUNK_X 16
#define CHUNK_Y 256
#define CHUNK_Z 16

#include <stdbool.h>
#include "../gfx/vao.h"
#include "../gfx/vbo.h"

struct Chunk {
    bool blocks[CHUNK_X][CHUNK_Y][CHUNK_Z];
    struct VAO vao;
    struct VBO vbo;
    int num_vertices;
};

void render_chunk(struct Chunk *self);
void chunk_create(struct Chunk *self);

#endif
