#include "camera.h"
#include "gfx/window.h"
#include <GL/gl.h>
#include <stdio.h>


void camera_init(Camera *cam) {
    glm_vec3_copy((vec3){0.0f, 0.0f, 3.0f}, cam->position);
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, cam->front);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, cam->up);

    cam->yaw = -90.0f;
    cam->pitch = 0.0f;
    cam->fov = 45.0f;
    cam->sens = 0.1f;
    cam->speed = 5.0f;
}

void camera_move(GLFWwindow *window, Camera *camera, float dt) {
    float cameraSpeed = camera->speed * dt;
    vec3 pos_diff = GLM_VEC3_ZERO_INIT;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        glm_vec3_scale(camera->front, cameraSpeed, pos_diff);
        glm_vec3_add(camera->position, pos_diff, camera->position);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        glm_vec3_scale(camera->front, cameraSpeed, pos_diff);
        glm_vec3_sub(camera->position, pos_diff, camera->position);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {

        glm_vec3_crossn(camera->front, camera->up, pos_diff);
        glm_vec3_scale(pos_diff, cameraSpeed, pos_diff);
        glm_vec3_sub(camera->position, pos_diff, camera->position);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm_vec3_crossn(camera->front, camera->up, pos_diff);
        glm_vec3_scale(pos_diff, cameraSpeed, pos_diff);
        glm_vec3_add(camera->position, pos_diff, camera->position);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        glm_vec3_scale((vec3){0.0f,1.0f,0.0f}, cameraSpeed, pos_diff);
        glm_vec3_add(camera->position, pos_diff,
                     camera->position);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        glm_vec3_scale((vec3){0.0f,1.0f,0.0f}, cameraSpeed, pos_diff);
        glm_vec3_sub(camera->position, pos_diff,
                     camera->position);
    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        if (win.isPolygonMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            win.isPolygonMode = false;
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            win.isPolygonMode = true;
        }
    }
}

void camera_mouse_movement(Camera *cam, float xOffset, float yOffset) {
    xOffset *= cam->sens;
    yOffset *= cam->sens;
    cam->yaw += xOffset;
    cam->pitch += yOffset;

    if (cam->pitch > 89.0f)
        cam->pitch = 89.0f;
    if (cam->pitch < -89.0f)
        cam->pitch = -89.0f;

    camera_update_vectors(cam);
}
void camera_update_vectors(Camera *cam) {
    vec3 dir;
    dir[0] = cos(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    dir[1] = sin(glm_rad(cam->pitch));
    dir[2] = sin(glm_rad(cam->yaw)) * cos(glm_rad(cam->pitch));
    glm_vec3_normalize_to(dir,cam->front);
    glm_vec3_crossn(cam->front, (vec3){0.0f,1.0f,0.0f}, cam->right);
    glm_vec3_crossn(cam->right, cam->front, cam->up);
}


void camera_get_view_matrix(Camera *cam, mat4 *dest) {

    vec3 target;
    glm_vec3_add(cam->position, cam->front, target);
    glm_lookat(cam->position, target, cam->up, dest[0]);
}
