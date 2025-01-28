#include "gfx/window.h"
#include "gfx/shader.h"

#include "gfx/vao.h"
#include "gfx/texture.h"
#include <GL/glext.h>
#include <stdio.h>

#include "block/block.h"
#include "cglm/mat4.h"
#include "camera.h"


// GLOBAL WINDOW
// GLFWwindow *win;
// struct Window win;
Camera cam;

float dt = 0.0f;
float lt = 0.0f;

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    float xpos = xposIn;
    float ypos = yposIn;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera_mouse_movement(&cam, xoffset, yoffset);
}

void processInput(GLFWwindow *window, Camera *camera) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    camera_move(window, camera, dt);
}

int main() {
    window_init();
    glfwSetCursorPosCallback(win.handle, mouse_callback);

    camera_init(&cam);

    struct Shader block_s = shader_create("../res/shaders/block_vert.glsl",
                                   "../res/shaders/block_frag.glsl");
    struct Texture block_t = texture_load("../res/textures/hisocarl.jpg", JPG,
                                          GL_TEXTURE_2D);
    struct VAO block_vao = block_create();

    int len = 20;

    while (!glfwWindowShouldClose(win.handle)) {
        float currentFrame = glfwGetTime();
        dt = currentFrame - lt;
        lt = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_bind(block_s);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, block_t.handle);


        processInput(win.handle, &cam);

        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 projection = GLM_MAT4_IDENTITY_INIT;

        camera_get_view_matrix(&cam, &view);

        glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT,
                        0.1f, 100.0f, projection);

        shader_uniform_mat4(block_s, "v", &view);
        shader_uniform_mat4(block_s, "p", &projection);

        vao_bind(block_vao);


        for (int x = 0; x < len; x++) {

            for (int y = 0; y < len; y++) {

                for (int z = 0; z < len; z++) {

                    mat4 model = GLM_MAT4_IDENTITY_INIT;

                    glm_translate(model, (vec3){x * 0.5, y * 0.5, z * -0.5});
                    glm_scale(model, (vec3){0.5,0.5,0.5});

                    shader_uniform_mat4(block_s, "m", &model);

                    glDrawArrays(GL_TRIANGLES, 0, 36);

                }
            }
        }

        glfwSwapBuffers(win.handle);
        glfwPollEvents();
    }

    glfwTerminate();
}
