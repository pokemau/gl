#include "gfx/gfx.h"
#include "gfx/window.h"
#include "gfx/shader.h"

#include "gfx/vao.h"
#include "gfx/texture.h"
#include <GL/glext.h>
#include <stdio.h>

#include "block/block.h"
#include "cglm/mat4.h"
#include "camera.h"

#include "world/chunk.h"
#include "world/cubemap.h"

// GLOBAL WINDOW
// GLFWwindow *win;
// struct Window win;
Camera cam;

int len = 70;
vec3 positions[] = {
    {1.0f, 0.0f, 0.0f},
};

chunk_t c;

int main() {

    window_init();
    camera_init(&cam);
    win.cam = &cam;

    shader_t block_s = shader_create("./res/shaders/block_vert.glsl",
                                     "./res/shaders/block_frag.glsl");
    texture_t block_t =
        texture_load("./res/textures/room.jpg", JPG, GL_TEXTURE_2D);

    chunk_create(&c);

    cubemap_t sb = cubemap_create();

    while (!glfwWindowShouldClose(win.handle)) {
        float currentFrame = glfwGetTime();
        win.dt = currentFrame - win.lt;
        win.lt = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window_process_input(win.handle, &cam, win.dt);

        shader_bind(block_s);
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 projection = GLM_MAT4_IDENTITY_INIT;
        camera_get_view_matrix(&cam, &view);
        glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT,
                        0.1f, 100.0f, projection);

        shader_uniform_mat4(block_s, "m", &model);
        shader_uniform_mat4(block_s, "v", &view);
        shader_uniform_mat4(block_s, "p", &projection);

        // draw chunk
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, block_t.handle);
        chunk_render(&c);


        // draw skybox
        glDepthFunc(GL_LEQUAL);
        shader_bind(sb.shd);
        mat4 sb_view;
        glm_mat4_copy(view, sb_view);
        sb_view[3][0] = sb_view[3][1] = sb_view[3][2] = 0.0f;
        shader_uniform_mat4(sb.shd, "view", &sb_view);
        shader_uniform_mat4(sb.shd, "projection", &projection);
        vao_bind(sb.vao);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, sb.tex.handle);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

        glfwSwapBuffers(win.handle);
        glfwPollEvents();
    }

    glfwTerminate();
}
