#include "System/Window.h"

namespace Window
{
    GLFWwindow *window;
    GLFWmonitor *monitor;
    const GLFWvidmode *mode;
    int width, height;
    int innerHeight;
    int cursorYOffset;
    const char *title;

    GLFWwindow *createWindow(const char *Title)
    {
        title = Title;
        monitor = glfwGetPrimaryMonitor();
        mode = glfwGetVideoMode(monitor);
        width = mode->width, height = mode->height;
        window = glfwCreateWindow(mode->width, mode->height, title, NULL, NULL);
        glfwGetWindowSize(window, NULL, &innerHeight);
        cursorYOffset = height - innerHeight;
        return window;
    }

    void setWidth(int Width) { width = Width; }
    void setHeight(int Height) { height = Height; }

    void setTitle(const char *Title)
    {
        title = Title;
        glfwSetWindowTitle(window, title);
    }

    GLFWwindow *getWindow() { return window; }
}