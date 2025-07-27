#include "cglm/types.h"
#include "gfx/gfx.h"
#include "gfx/shader.h"
#include "gfx/window.h"

#include "gfx/texture.h"
#include "gfx/vao.h"
#include <GL/glext.h>

#include "block/block.h"
#include "camera.h"
#include "cglm/mat4.h"

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

    shader_t block_shd = shader_create("./res/shaders/block_vert.glsl",
                                       "./res/shaders/block_frag.glsl");
    texture_t block_t =
        texture_load("./res/textures/room.jpg", JPG, GL_TEXTURE_2D);

    chunk_create(&c);

    cubemap_t sb = cubemap_create();

    shader_t cube_shd = shader_create("./res/shaders/light/cube_vert.glsl",
                                      "./res/shaders/light/cube_frag.glsl");
    shader_t light_shd = shader_create("./res/shaders/light/light_vert.glsl",
                                       "./res/shaders/light/light_frag.glsl");

    vao_t cube = block_create();
    vao_t light_cube = block_create();

    texture_t container_diffuse_tx =
        texture_load("./res/textures/container.png", PNG, GL_TEXTURE_2D);
    texture_t container_specular_tx = texture_load(
        "./res/textures/container2_specular.png", PNG, GL_TEXTURE_2D);

    shader_bind(cube_shd);
    shader_uniform_int(cube_shd, "material.diffuse", 0);
    shader_uniform_int(cube_shd, "material.specular", 1);

    while (!glfwWindowShouldClose(win.handle)) {
        float currentFrame = glfwGetTime();
        win.dt = currentFrame - win.lt;
        win.lt = currentFrame;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window_process_input(win.handle, &cam, win.dt);

        shader_bind(block_shd);
        mat4 model = GLM_MAT4_IDENTITY_INIT;
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 projection = GLM_MAT4_IDENTITY_INIT;
        camera_get_view_matrix(&cam, &view);
        glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT,
                        0.1f, 100.0f, projection);

        shader_uniform_mat4(block_shd, "m", &model);
        shader_uniform_mat4(block_shd, "v", &view);
        shader_uniform_mat4(block_shd, "p", &projection);

        vec3 lightPos = {2.0f, 0.0f, 2.0f};
        vec3 lightColor = {1.0f, 1.0f, 1.0f};

        lightPos[0] = 1.0f + sin(glfwGetTime()) * 5.0f;
        lightPos[1] = sin(glfwGetTime() / 2.0f) * 1.0f;

        // lightColor[0] = 1.0f + sin(glfwGetTime()) * 2.0f;
        // lightColor[1] = sin(glfwGetTime() / 2.0f) * 1.0f;

        // DRAW_CUBE
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, container_diffuse_tx.handle);
        shader_bind(cube_shd);
        shader_uniform_vec3(cube_shd, "objectColor",
                            &((vec3){1.0f, 1.0f, 1.0}));
        shader_uniform_vec3(cube_shd, "lightColor", &lightColor);

        shader_uniform_vec3(cube_shd, "light.position", &lightPos);
        shader_uniform_vec3(cube_shd, "viewPos", &cam.position);

        // material
        shader_uniform_float(cube_shd, "material.shininess", 64.0f);

        // light
        shader_uniform_vec3(cube_shd, "light.ambient",
                            &(vec3){0.2f, 0.2f, 0.2f});
        shader_uniform_vec3(cube_shd, "light.diffuse",
                            &(vec3){0.5f, 0.5f, 0.5f});
        shader_uniform_vec3(cube_shd, "light.specular",
                            &(vec3){1.0f, 1.0f, 1.0f});

        shader_uniform_mat4(cube_shd, "projection", &projection);
        shader_uniform_mat4(cube_shd, "view", &view);

        mat4 m = GLM_MAT4_IDENTITY_INIT;
        shader_uniform_mat4(cube_shd, "model", &m);

        vao_bind(cube);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // --- DRAW_CUBE

        // DRAW_LIGHT_SOURCE
        shader_bind(light_shd);
        shader_uniform_mat4(light_shd, "projection", &projection);
        shader_uniform_mat4(light_shd, "view", &view);
        shader_uniform_vec3(light_shd, "lightColor", &lightColor);
        glm_translate(model, lightPos);
        glm_scale(model, (vec3){0.5f, 0.5f, 0.5f});
        shader_uniform_mat4(light_shd, "model", &model);
        vao_bind(light_cube);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // --- DRAW_LIGHT_SOURCE

        // draw chunk
        // shader_bind(block_shd);
        // shader_uniform_vec3(block_shd, "objectColor",
        //                     &((vec3){1.0f, 0.5f, 0.31f}));
        // shader_uniform_vec3(block_shd, "lightColor", &lightColor);
        // shader_uniform_vec3(cube_shd, "lightPos", &lightPos);
        //
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, block_t.handle);
        // chunk_render(&c);

        // draw skybox
        // glDepthFunc(GL_LEQUAL);
        // shader_bind(sb.shd);
        // mat4 sb_view;
        // glm_mat4_copy(view, sb_view);
        // sb_view[3][0] = sb_view[3][1] = sb_view[3][2] = 0.0f;
        // shader_uniform_mat4(sb.shd, "view", &sb_view);
        // shader_uniform_mat4(sb.shd, "projection", &projection);
        // vao_bind(sb.vao);
        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_CUBE_MAP, sb.tex.handle);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        // glBindVertexArray(0);
        // glDepthFunc(GL_LESS);

        glfwSwapBuffers(win.handle);
        glfwPollEvents();
    }

    glfwTerminate();
}
