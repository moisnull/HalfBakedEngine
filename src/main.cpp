#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "render.h"

struct color {
    float red, green, blue, alpha;
};

constexpr color color = {
    .red = 0.35f, .green = 0.65f, .blue = 0.73f, .alpha = 0.0f
};

GLFWwindow* window;

unsigned int SCREEN_WIDTH = 800;
unsigned int SCREEN_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void getResolution();
void processInput(GLFWwindow *window);
int handleDisplay(GLFWwindow *window);

int main()
{
    handleDisplay(window);
    render();
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void getResolution() {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    SCREEN_WIDTH = mode->width, SCREEN_HEIGHT = mode->height;
}

void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

int handleDisplay(GLFWwindow *window) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    getResolution();

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        glClearColor(color.red, color.green, color.blue, color.alpha);
        glClear(GL_COLOR_BUFFER_BIT);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}