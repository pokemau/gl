#include "texture.h"

#include "stb_image.h"
#include <stdbool.h>

texture_t texture_load(const char *texture_path, enum TextureType type,
                            GLenum target) {
    texture_t self;
    glGenTextures(1, &self.handle);
    glBindTexture(GL_TEXTURE_2D, self.handle);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load(texture_path, &width, &height, &nrChannels, 0);

    if (data) {

        if (type == JPG) {
            glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
        } else if (type == PNG) {
            glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(target);
    } else {
        printf("ERROR TEXTURE_LOAD\n");
    }
    stbi_image_free(data);

    return self;
}
