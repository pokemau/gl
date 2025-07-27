#include "shader.h"
#include "gfx.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static void _log_and_fail(GLint handle, const char *adverb, const char *path,
                          void (*getlog)(GLuint, GLsizei, GLsizei *, GLchar *),
                          void (*getiv)(GLuint, GLenum, GLint *)) {
    GLint loglen;
    getiv(handle, GL_INFO_LOG_LENGTH, &loglen);

    char *logtext = calloc(1, loglen);
    getlog(handle, loglen, NULL, logtext);
    fprintf(stderr, "Error %s shader at %s:\n%s", adverb, path, logtext);

    free(logtext);
    exit(1);
}

static GLint _compile(const char *path, GLenum type) {
    FILE *f;
    char *text;
    long len;

    f = fopen(path, "rb");
    if (f == NULL) {
        fprintf(stderr, "error loading shader at %s\n", path);
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    text = calloc(1, len);
    fread(text, 1, len, f);
    fclose(f);

    GLuint handle = glCreateShader(type);
    glShaderSource(handle, 1, (const GLchar *const *)&text,
                   (const GLint *)&len);
    glCompileShader(handle);

    GLint compiled;
    glGetShaderiv(handle, GL_COMPILE_STATUS, &compiled);

    // Check OpenGL logs if compilation failed
    if (compiled == 0) {
        _log_and_fail(handle, "compiling", path, glGetShaderInfoLog,
                      glGetShaderiv);
    }

    free(text);
    return handle;
}

shader_t shader_create(const char *vs_path, const char *fs_path) {
    shader_t self;
    self.vs_handle = _compile(vs_path, GL_VERTEX_SHADER);
    self.fs_handle = _compile(fs_path, GL_FRAGMENT_SHADER);
    self.handle = glCreateProgram();

    glAttachShader(self.handle, self.vs_handle);
    glAttachShader(self.handle, self.fs_handle);

    glLinkProgram(self.handle);

    GLint linked;
    glGetProgramiv(self.handle, GL_LINK_STATUS, &linked);

    if (linked == 0) {
        char buf[512];
        snprintf(buf, 512, "[%s, %s]", vs_path, fs_path);
        _log_and_fail(self.handle, "linking", buf, glGetProgramInfoLog,
                      glGetProgramiv);
    }

    glDetachShader(self.handle, self.vs_handle);
    glDetachShader(self.handle, self.fs_handle);
    glDeleteShader(self.vs_handle);
    glDeleteShader(self.fs_handle);
    return self;
}

void shader_destroy(shader_t self) {
    glDeleteProgram(self.handle);
    glDeleteShader(self.fs_handle);
    glDeleteShader(self.vs_handle);
}

void shader_bind(shader_t self) { glUseProgram(self.handle); }

void shader_uniform_int(shader_t self, const char *name, int v) {
    glUniform1i(glGetUniformLocation(self.handle, name), v);
}

void shader_uniform_mat4(shader_t self, const char *name, mat4 *m) {
    glUniformMatrix4fv(glGetUniformLocation(self.handle, name), 1, GL_FALSE,
                       *(m[0]));
}
void shader_uniform_vec3(shader_t self, const char *name, vec3 *v) {
    glUniform3fv(glGetUniformLocation(self.handle, name), 1, v[0]);
}

void shader_uniform_float(shader_t self, const char *name, float f) {
    glUniform1f(glGetUniformLocation(self.handle, name), f);
}
