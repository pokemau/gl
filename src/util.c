#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "stb_image.h"

GLFWwindow *createWindow(void) {
    int window_w = WINDOW_WIDTH;
    int window_h = WINDOW_HEIGHT;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    return glfwCreateWindow(window_w, window_h, "GL", NULL, NULL);
}

GLuint make_shader(GLenum type, const char *source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = calloc(length, sizeof(GLchar));
        glGetShaderInfoLog(shader, length, NULL, info);
        fprintf(stderr, "glCompileShader failed:\n%s\n", info);
        free(info);
    }
    return shader;
}

GLuint load_shader(GLenum type, const char *path) {
    char *data = load_file(path);
    GLuint result = make_shader(type, data);
    free(data);
    return result;
}

GLuint make_shader_program(GLuint shader1, GLuint shader2) {
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, shader1);
    glAttachShader(shaderProgram, shader2);
    glLinkProgram(shaderProgram);

    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint length;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
        GLchar *info = calloc(length, sizeof(char));
        glGetProgramInfoLog(shaderProgram, length, NULL, info);
        fprintf(stderr, "ERROR::MAKE_SHADER_PROGRAM::%s\n", info);
        free(info);
    }

    glDetachShader(shaderProgram, shader1);
    glDetachShader(shaderProgram, shader2);
    glDeleteShader(shader1);
    glDeleteShader(shader2);
    return shaderProgram;
}

GLuint load_texture2D(const char *path, enum IMAGE_TYPE type) {
    GLuint ID;
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data) {
        if (type == JPG) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                         GL_UNSIGNED_BYTE, data);
        } else if (type == PNG) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fprintf(stderr, "ERROR::TEXTURE::LOAD::%s\n", path);
    }
    stbi_image_free(data);
    return ID;
}
void setShaderMat4(GLuint shaderProg, const char *name, mat4 *data) {
    GLuint projLoc = glGetUniformLocation(shaderProg, name);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, *(data[0]));
}

char *load_file(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) {
        fprintf(stderr, "failed to open %s\n", path);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    int len = ftell(file);
    rewind(file);
    char *data = calloc(len + 1, sizeof(char));
    fread(data, 1, len, file);
    fclose(file);
    return data;
}
