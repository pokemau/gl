#ifndef _camera_h_
#define _camera_h_

#include "gfx/gfx.h"
#include <cglm/cglm.h>

typedef struct {
    vec3 position;
    vec3 front;
    vec3 up;
    vec3 right;
    float yaw;
    float pitch;
    float fov;
    float sens;
    float speed;
} Camera ;

void camera_mouse_movement(Camera *cam, float xOffset, float yOffset);
void camera_update_vectors(Camera *cam);
void camera_init(Camera *cam);
void camera_get_view_matrix(Camera *cam, mat4 *target);

void camera_move(GLFWwindow *window, Camera *camera, float dt);

void move_forward(Camera *cam, float dt);
void move_left(Camera *cam, float dt);
void move_backward(Camera *cam, float dt);
void move_right(Camera *cam, float dt);

#endif
