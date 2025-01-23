#include "gfx/window.h"
#include "gfx/shader.h"

#include "gfx/vao.h"
#include "gfx/texture.h"
#include <GL/glext.h>
#include <stdio.h>

#include "cglm/mat4.h"

#include "camera.h"

// GLOBAL WINDOW
GLFWwindow *win;
Camera cam;

float dt = 0.0f;
float lt = 0.0f;

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

int main() {
    win = window_create();

    struct Shader s;
    struct Texture t;

    s = shader_create("../res/vertex.glsl", "../res/fragment.glsl");
    t = texture_load("../res/textures/hisocarl.jpg", JPG, GL_TEXTURE_2D);

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    struct VAO vao = vao_create();
    struct VBO vbo = vbo_create(GL_ARRAY_BUFFER, false);
    struct VBO ebo = vbo_create(GL_ELEMENT_ARRAY_BUFFER, false);

    vbo_buffer(vbo, vertices, sizeof(vertices));
    vbo_buffer(ebo, indices, sizeof(indices));

    vao_attr(vao, ebo, 0, 3, GL_FLOAT, 8 * sizeof(float), 0);
    vao_attr(vao, ebo, 1, 3, GL_FLOAT, 8 * sizeof(float), 3 * sizeof(float));
    vao_attr(vao, ebo, 2, 2, GL_FLOAT, 8 * sizeof(float), 6 * sizeof(float));

    //    shader_bind(s);
    //    shader_uniform_int(s, "texture1", 0);

    //    shader_bind(s);
    //    shader_uniform_int(s, "texture1", 0);

    while (!glfwWindowShouldClose(win)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, t.handle);

        shader_bind(s);

        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        mat4 projection = GLM_MAT4_IDENTITY_INIT;

        glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});

        glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT,
                        0.1f, 100.0f, projection);

        glm_rotate(model, glm_rad(-55.0f), (vec3){1.0f, 0.0f, 0.0f});
        glm_scale(model, (vec3){1.0f, 1.0f, 1.0f});

        shader_uniform_mat4(s, "model", &model);
        shader_uniform_mat4(s, "view", &view);
        shader_uniform_mat4(s, "projection", &projection);

        vao_bind(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

//        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
}
