#ifndef _util_h_
#define _util_h_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include "camera.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 500

typedef enum {
    PNG, JPG
} image_type_e;

GLFWwindow *createWindow(void);
GLuint load_shader(GLenum type, const char *path);
GLuint make_shader(GLenum type, const char *source);
GLuint make_shader_program(GLuint shader1, GLuint shader2);
GLuint load_texture2D(const char *path, image_type_e type);
char *load_file(const char *path);
void setShaderMat4(GLuint shaderProg, const char *name, mat4 *data);

#endif
