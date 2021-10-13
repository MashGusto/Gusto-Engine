#pragma once

#include "GLFW/glfw3.h"

namespace Window
{
    extern GLFWwindow *window;
    extern GLFWmonitor *monitor;
    extern const GLFWvidmode *mode;
    extern int width, height;
    extern int innerHeight;
    extern int cursorYOffset;
    extern const char *title;

    GLFWwindow *createWindow(const char *Title);

    void setWidth(int Width);
    void setHeight(int Height);
    void setTitle(const char *Title);

    GLFWwindow *getWindow();
}