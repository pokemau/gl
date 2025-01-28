#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "gfx.h"
#include <stdbool.h>

enum PolygonMode {
    FULL, LINES
};

struct Window {
    GLFWwindow *handle;
    bool isPolygonMode;
};

extern struct Window win;

void window_init();
GLFWwindow *window_create();

#endif
