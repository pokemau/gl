#ifndef _VAO_H_
#define _VAO_H_


#include "gfx.h"
#include "vbo.h"

typedef struct {
    GLuint handle;
} vao_t;

vao_t vao_create();
void vao_bind(vao_t self);
void vao_destroy(vao_t self);
void vao_attr(vao_t self, vbo_t vbo, GLuint index,
              GLuint size, GLenum type, GLsizei stride, size_t offset);

#endif
