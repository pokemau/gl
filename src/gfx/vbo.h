#ifndef _VBO_H_
#define _VBO_H_

#include "gfx.h"
#include <stdbool.h>

typedef struct {
    GLuint handle;
    GLint type;
    bool dynamic;
} vbo_t;

vbo_t vbo_create(GLint type, bool dynamic);
void vbo_bind(vbo_t self);
void vbo_destroy(vbo_t self);
// void vbo_buffer(vbo_t self, void *data, size_t offset, size_t count);
void vbo_buffer(vbo_t self, void *data, size_t size);

#endif
