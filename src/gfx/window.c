#include "window.h"

#include "../util.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow *window_create() {

    GLFWwindow *win;

    glfwInit();

    if (!glfwInit()) {
        fprintf(stderr, "%s",  "error initializing GLFW\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GL", NULL, NULL);

    if (!win) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        exit(1);
    }

    glfwSwapInterval(0);

    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
    glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("Failed to initialize GLAD\n");
        exit(1);
    }

    glEnable(GL_DEPTH_TEST);

    return win;
}
