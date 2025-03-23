#include "vbo.h"

vbo_t vbo_create(GLint type, bool dynamic) {
    vbo_t self = {
        .type = type,
        .dynamic = dynamic
    };
    glGenBuffers(1, &self.handle);
    return self;
};

void vbo_bind(vbo_t self) {
    glBindBuffer(self.type, self.handle);
}

void vbo_destroy(vbo_t self) {
    glDeleteBuffers(1, &self.handle);
}

void vbo_buffer(vbo_t self, void *data, size_t size) {
    vbo_bind(self);
    glBufferData(self.type,
                 size,
                 data,
                 self.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
