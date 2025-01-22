#include "vao.h"

#include "gfx.h"

struct VAO vao_create() {
    struct VAO self;
    glGenVertexArrays(1, &self.handle);
    return self;
}

void vao_bind(struct VAO self) {
    glBindVertexArray(self.handle);
}

void vao_destroy(struct VAO self) {
    glDeleteVertexArrays(1, &self.handle);
}

void vao_attr(struct VAO self, struct VBO vbo, GLuint index,
              GLuint size, GLenum type, GLsizei stride, size_t offset) {
    vao_bind(self);
    vbo_bind(vbo);

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride,
                          (void *) offset);
}
