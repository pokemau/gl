#include "vao.h"

#include "gfx.h"

vao_t vao_create() {
    vao_t self;
    glGenVertexArrays(1, &self.handle);
    return self;
}

void vao_bind(vao_t self) {
    glBindVertexArray(self.handle);
}

void vao_destroy(vao_t self) {
    glDeleteVertexArrays(1, &self.handle);
}

void vao_attr(vao_t self, vbo_t vbo, GLuint index,
              GLuint size, GLenum type, GLsizei stride, size_t offset) {
    vao_bind(self);
    vbo_bind(vbo);

    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, type, GL_FALSE, stride,
                          (void *) offset);
}
