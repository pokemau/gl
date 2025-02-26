#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "gfx.h"
#include "../camera.h"
#include <stdbool.h>

enum PolygonMode {
    FULL, LINES
};

struct Window {
    GLFWwindow *handle;
    bool isPolygonMode;

    bool first_mouse;
    float last_x, last_y;
    float dt, lt;

    Camera *cam;
};

extern struct Window win;

void window_init();
GLFWwindow *window_create();

void window_process_input(GLFWwindow *window, Camera *camera, float dt);

#endif
