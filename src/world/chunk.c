#include "chunk.h"
#include <stdio.h>
#include <stdlib.h>

void render_chunk(struct Chunk *self) {
    vao_bind(self->vao);
    glDrawArrays(GL_TRIANGLES, 0, self->num_vertices);
}

void chunk_create(struct Chunk *self) {
    for (int x = 0; x < CHUNK_X; x++) {
        for (int y = 0; y < CHUNK_Y; y++) {
            for (int z = 0; z < CHUNK_Z; z++) {
                self->blocks[x][y][z] = true;
            }
        }
    }

    int max = CHUNK_X * CHUNK_Y * CHUNK_Z * 36 * 5;

    float *vertices = malloc(max * sizeof(float));
    if (vertices == NULL) {
        fprintf(stderr, "FAILED TO ALLOC: [chunk.c]");
        exit(1);
    }

    int index = 0;

    for (int x = 0; x < CHUNK_X; x++) {
        for (int y = 0; y < CHUNK_Y; y++) {
            for (int z = 0; z < CHUNK_Z; z++) {
                if (self->blocks[x][y][z] == true) {
                    if (index + 36 > max) {
                        fprintf(stderr, "Error: Vertex buffer overflow!\n");
                        free(vertices);
                        exit(1);
                    }

                    if (z == 0) {
                        // Back face
                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z;
                        vertices[index++] = 1;
                        vertices[index++] = 1;

                        vertices[index++] = x + 1;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 1;
                        vertices[index++] = 0;

                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x;
                        vertices[index++] = y + 1;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 1;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z;
                        vertices[index++] = 1;
                        vertices[index++] = 1;
                    }

                    if (z == CHUNK_Z - 1) {
                        // Front face
                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z + 1;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 1;

                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z + 1;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 1;

                        vertices[index++] = x;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 0;
                        vertices[index++] = 1;
                    }

                    if (x == 0) {
                        // Left face
                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 0;

                        vertices[index++] = x;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 1;

                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 1;

                        vertices[index++] = x;
                        vertices[index++] = y + 1;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 1;
                    }

                    if (x == CHUNK_X - 1) {
                        // Right face
                        vertices[index++] = x + 1;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 1;

                        vertices[index++] = x + 1;
                        vertices[index++] = y;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 1;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 1;
                    }

                    if (y == CHUNK_Y - 1) {
                        // Top face
                        vertices[index++] = x;
                        vertices[index++] = y + 1;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 1;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z;
                        vertices[index++] = 1;
                        vertices[index++] = 1;

                        vertices[index++] = x;
                        vertices[index++] = y + 1;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 1;

                        vertices[index++] = x;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 0;
                        vertices[index++] = 0;

                        vertices[index++] = x + 1;
                        vertices[index++] = y + 1;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 0;
                    }

                    if (y == 0) {

                        // Bottom face
                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 1;

                        vertices[index++] = x + 1;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 1;
                        vertices[index++] = 1;

                        vertices[index++] = x + 1;
                        vertices[index++] = y;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 0;

                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z;
                        vertices[index++] = 0;
                        vertices[index++] = 1;

                        vertices[index++] = x + 1;
                        vertices[index++] = y;
                        vertices[index++] = z + 1;
                        vertices[index++] = 1;
                        vertices[index++] = 0;

                        vertices[index++] = x;
                        vertices[index++] = y;
                        vertices[index++] = z + 1;
                        vertices[index++] = 0;
                        vertices[index++] = 0;
                    }
                }
            }
        }
    }

    self->num_vertices = index / 3;

    self->vao = vao_create();
    self->vbo = vbo_create(GL_ARRAY_BUFFER, false);

    vbo_buffer(self->vbo, vertices, sizeof(float) * index);
    vao_attr(self->vao, self->vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);
    vao_attr(self->vao, self->vbo, 1, 2, GL_FLOAT, 5 * sizeof(float),
             3 * sizeof(float));
}
