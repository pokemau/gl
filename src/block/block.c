#include "block.h"

// float vertices[] = {
//     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bot left
//     0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, // bot right
//     0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // top right
//     0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // top right
//     -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, // top left
//     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bot left
// 
//     -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // bot left
//     0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, // bot right
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
//     -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, // top left
//     -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // bot left
// 
//     -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // bot left
//     -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, // bot right
//     -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, // top right
//     -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, // top right
//     -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, // top left
//     -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, // bot left
// 
//     0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, // bot left
//     0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, // bot right
//     0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // top right
//     0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // top right
//     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top left
//     0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, // bot left
// 
//     -0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, // bot left
//     0.5f,  0.5f,  -0.5f, 1.0f, 0.0f, // bot right
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
//     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top right
//     -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, // top left
//     -0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, // bot left
// 
//     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bot left
//     0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, // bot right
//     0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, // top right
//     0.5f,  -0.5f, 0.5f,  1.0f, 1.0f, // top right
//     -0.5f, -0.5f, 0.5f,  0.0f, 1.0f, // top left
//     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bot left
// };

float cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    // Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    // Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    // Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
};

struct VAO block_create() {
    struct VAO self;
    struct VBO vbo;

    self = vao_create();
    vbo = vbo_create(GL_ARRAY_BUFFER, false);

    vbo_buffer(vbo, cubeVertices, sizeof(cubeVertices));

    // position
    vao_attr(self, vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), 0);

    // texture
    vao_attr(self, vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), 3 * sizeof(float));

    return self;
}
