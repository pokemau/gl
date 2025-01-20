#include "gfx/window.h"
#include "gfx/shader.h"

#include "util.h"
#include "util/vec.h"

#include <stdio.h>

// GLOBAL WINDOW
GLFWwindow *win;

int main(int argc, char* argv[]) {
    win = window_create();

    struct Shader s;
    s = shader_create("../res/vertex.glsl", "../res/fragment.glsl");

    while (!glfwWindowShouldClose(win)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(win);
        glfwPollEvents();
    }

    glfwTerminate();
}

