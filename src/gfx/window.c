#include "window.h"

#include "../util.h"
#include "GLFW/glfw3.h"

struct Window win;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_E && action == GLFW_PRESS) {
        // Toggle polygon mode
        if (win.isPolygonMode) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            win.isPolygonMode = false;
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            win.isPolygonMode = true;
        }
    }
}

static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    float xpos = xposIn;
    float ypos = yposIn;

    if (win.first_mouse) {
        win.last_x = xpos;
        win.last_y = ypos;
        win.first_mouse = false;
    }

    float xoffset = xpos - win.last_x;
    float yoffset = win.last_y - ypos;
    win.last_x = xpos;
    win.last_y = ypos;

    camera_mouse_movement(win.cam, xoffset, yoffset);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void window_init() {
    win.handle = window_create();
    win.isPolygonMode = false;
    win.first_mouse = true;
    win.last_x = 800.0f / 2.0;
    win.last_y = 600.0 / 2.0;
    win.dt = 0.0f;
    win.lt = 0.0f;

    glfwSetCursorPosCallback(win.handle, mouse_callback);
    glfwSetKeyCallback(win.handle, key_callback);
}

GLFWwindow *window_create() {

    GLFWwindow *win;

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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    return win;
}
void window_process_input(GLFWwindow *window, Camera *camera, float dt) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    camera_move(window, camera, dt);
}

