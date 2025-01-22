#ifndef _VBO_H_
#define _VBO_H_

#include "gfx.h"
#include <stdbool.h>

struct VBO {
    GLuint handle;
    GLint type;
    bool dynamic;
};

struct VBO vbo_create(GLint type, bool dynamic);
void vbo_bind(struct VBO self);
void vbo_destroy(struct VBO self);
// void vbo_buffer(struct VBO self, void *data, size_t offset, size_t count);
void vbo_buffer(struct VBO self, void *data, size_t size);

#endif
