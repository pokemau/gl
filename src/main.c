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
GLFWwindow *win;
Camera cam;

float dt = 0.0f;
float lt = 0.0f;

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

int main() {
    win = window_create();


    struct Shader block_s = shader_create("../res/shaders/block_vert.glsl",
                                   "../res/shaders/block_frag.glsl");
    struct Texture block_t = texture_load("../res/textures/wall.jpg", JPG,
                                          GL_TEXTURE_2D);
    struct VAO block_vao = block_create();

    vec3 positions[] = {
        {0,7,0},
        {2,5,-15},
        {-1.5,2.2,-2.5},
    };

    while (!glfwWindowShouldClose(win)) {

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        shader_bind(block_s);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, block_t.handle);


        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 projection = GLM_MAT4_IDENTITY_INIT;

        glm_translate(view, (vec3){0.0f, 0.0f, -10.0f});
        glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT,
                        0.1f, 100.0f, projection);

        shader_uniform_mat4(block_s, "v", &view);
        shader_uniform_mat4(block_s, "p", &projection);


        vao_bind(block_vao);

        for (int i = 0; i < 3; i++) {
            mat4 model = GLM_MAT4_IDENTITY_INIT;
            glm_translate(model, positions[i]);
            glm_rotate(model, glm_rad(-55.0f), (vec3){1.0f, 0.0f, 0.0f});
            shader_uniform_mat4(block_s, "m", &model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
}
