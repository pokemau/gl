#include "gfx/window.h"
#include "gfx/shader.h"

#include "gfx/vao.h"
#include "gfx/texture.h"
#include <GL/glext.h>
#include <stdio.h>

#include "block/block.h"
#include "cglm/mat4.h"
#include "camera.h"

#include "block/chunk.h"


// GLOBAL WINDOW
// GLFWwindow *win;
// struct Window win;
Camera cam;


int len = 10;
vec3 positions[] = {
    {1.0f, 0.0f, 0.0f},
};

struct Chunk c;

int main() {
    window_init();
    camera_init(&cam);
    win.cam = &cam;


    struct Shader block_s = shader_create("./res/shaders/block_vert.glsl",
                                   "./res/shaders/block_frag.glsl");
    struct Texture block_t = texture_load("./res/textures/hisocarl.jpg", JPG,
                                          GL_TEXTURE_2D);
    struct VAO block_vao = block_create();

    chunk_create(&c);

    while (!glfwWindowShouldClose(win.handle)) {
        float currentFrame = glfwGetTime();
        win.dt = currentFrame - win.lt;
        win.lt = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader_bind(block_s);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, block_t.handle);

        window_process_input(win.handle, &cam, win.dt);

        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 projection = GLM_MAT4_IDENTITY_INIT;

        camera_get_view_matrix(&cam, &view);

        glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT,
                        0.1f, 100.0f, projection);

        shader_uniform_mat4(block_s, "v", &view);
        shader_uniform_mat4(block_s, "p", &projection);

        mat4 model = GLM_MAT4_IDENTITY_INIT;
        shader_uniform_mat4(block_s, "m", &model);

        vao_bind(c.vao);
        glDrawArrays(GL_TRIANGLES, 0, c.num_vertices);

//        vao_bind(block_vao);
//        glDrawArrays(GL_TRIANGLES, 0, 36);






//        for (int x = 0; x < len; x++) {
//
//            for (int y = 0; y < len; y++) {
//
//                for (int z = 0; z < len; z++) {
//
//                    mat4 model = GLM_MAT4_IDENTITY_INIT;
//
//                    glm_translate(model, (vec3){x * 0.8, y * 0.8, z * -0.8});
//                    glm_scale(model, (vec3){0.5,0.5,0.5});
//
//                    shader_uniform_mat4(block_s, "m", &model);
//
//
//                }
//            }
//        }

        glfwSwapBuffers(win.handle);
        glfwPollEvents();
    }

    glfwTerminate();
}
