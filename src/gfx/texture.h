#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "gfx.h"

enum TextureType {
    JPG,
    PNG
};

typedef struct {
    GLuint handle;
} texture_t;

texture_t texture_load(const char *texture_path, enum TextureType type,
                            GLenum target);

#endif
