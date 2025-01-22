#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "gfx.h"

enum TextureType {
    JPG,
    PNG
};

struct Texture {
    GLuint handle;
};

struct Texture texture_load(const char *texture_path, enum TextureType type,
                            GLenum target);

#endif
