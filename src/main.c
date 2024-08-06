#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdio.h>

#include "util.h"
#include "stb_image.h"
#include "camera.h"
#include "cglm/cam.h"
#include "cglm/vec3.h"

typedef struct {
    GLFWwindow *window;
} App;

static App app;
static App *g = &app;
Camera cam;

float dt = 0.0f;
float lt = 0.0f;

bool firstMouse = true;
float lastX = 800.0f / 2.0;
float lastY = 600.0 / 2.0;

void processInput(GLFWwindow *window, Camera *camera);
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);

int main(void) {

    init_camera(&cam);

    if (!glfwInit())
        return -1;

    g->window = createWindow();

    if (!g->window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(g->window);
    glfwSetCursorPosCallback(g->window, mouse_callback);
    glfwSetInputMode(g->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSwapInterval(0);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "FAILED TO INIT GLAD\n");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    GLuint vShader = load_shader(GL_VERTEX_SHADER, "./res/vertex.glsl");
    GLuint fShader = load_shader(GL_FRAGMENT_SHADER, "./res/fragment.glsl");
    GLuint shaderProgram = make_shader_program(fShader, vShader);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO); // bind VAO first
                            // then bind vbo, ebo and set buffer data

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                          (void *)(6 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint tex = load_texture2D("./res/wall.jpg", JPG);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(g->window)) {
        float currentFrame = glfwGetTime();
        dt = currentFrame - lt;
        lt = currentFrame;

        processInput(g->window, &cam);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);

        glBindVertexArray(VAO);

        mat4 model = GLM_MAT4_IDENTITY_INIT;
        mat4 view = GLM_MAT4_IDENTITY_INIT;
        mat4 projection = GLM_MAT4_IDENTITY_INIT;

        get_view_matrix(&cam, &view);

        glm_perspective(glm_rad(45.0f), (float)WINDOW_WIDTH / WINDOW_HEIGHT,
                        1.1f, 100.0f, projection);

        float angle = glfwGetTime() * 30.0f;
        glm_translate(model, (vec3){0.0f, 0.0f, -2.0f});
        glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.5f, 1.0f});
        glm_scale(model, (vec3){1.0f, 1.0f, 1.0f});

        setShaderMat4(shaderProgram, "view", &view);
        setShaderMat4(shaderProgram, "projection", &projection);
        setShaderMat4(shaderProgram, "model", &model);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(g->window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window, Camera *camera) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    camera_move(window, camera, dt);
}

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    float xpos = xposIn;
    float ypos = yposIn;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    camera_mouse_movement(&cam, xoffset, yoffset);
}
