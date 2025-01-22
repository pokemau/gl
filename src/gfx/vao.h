#ifndef _VAO_H_
#define _VAO_H_


#include "gfx.h"
#include "vbo.h"

struct VAO {
    GLuint handle;
};

struct VAO vao_create();
void vao_bind(struct VAO self);
void vao_destroy(struct VAO self);
void vao_attr(struct VAO self, struct VBO vbo, GLuint index,
              GLuint size, GLenum type, GLsizei stride, size_t offset);

#endif
