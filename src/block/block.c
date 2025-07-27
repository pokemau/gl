#include "block.h"

float cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
    -0.5f,  0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, // bottom-left
};

// float cubeVertices[] = {
//     -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f, 0.5f,  -0.5f, -0.5f,
//     0.0f,  0.0f,  -1.0f, 0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f,
//     0.5f,  0.5f,  -0.5f, 0.0f,  0.0f,  -1.0f, -0.5f, 0.5f,  -0.5f,
//     0.0f,  0.0f,  -1.0f, -0.5f, -0.5f, -0.5f, 0.0f,  0.0f,  -1.0f,
//
//     -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.5f,  -0.5f, 0.5f,
//     0.0f,  0.0f,  1.0f,  0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  -0.5f, 0.5f,  0.5f,
//     0.0f,  0.0f,  1.0f,  -0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,
//
//     -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  -0.5f,
//     -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,
//     -0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f,  -0.5f, -0.5f, 0.5f,
//     -1.0f, 0.0f,  0.0f,  -0.5f, 0.5f,  0.5f,  -1.0f, 0.0f,  0.0f,
//
//     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
//     1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,
//     0.5f,  -0.5f, -0.5f, 1.0f,  0.0f,  0.0f,  0.5f,  -0.5f, 0.5f,
//     1.0f,  0.0f,  0.0f,  0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
//
//     -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, -0.5f,
//     0.0f,  -1.0f, 0.0f,  0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,
//     0.5f,  -0.5f, 0.5f,  0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, 0.5f,
//     0.0f,  -1.0f, 0.0f,  -0.5f, -0.5f, -0.5f, 0.0f,  -1.0f, 0.0f,
//
//     -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  -0.5f,
//     0.0f,  1.0f,  0.0f,  0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
//     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  0.5f,
//     0.0f,  1.0f,  0.0f,  -0.5f, 0.5f,  -0.5f, 0.0f,  1.0f,  0.0f};

vao_t block_create() {
    vao_t self;
    vbo_t vbo;

    self = vao_create();
    vbo = vbo_create(GL_ARRAY_BUFFER, false);

    vbo_buffer(vbo, cubeVertices, sizeof(cubeVertices));

    // position
    vao_attr(self, vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);

    // texture
    // vao_attr(self, vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 *
    // sizeof(float));

    // normal
    vao_attr(self, vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (3 * sizeof(float)));
    vao_attr(self, vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (6 * sizeof(float)));

    return self;
}
