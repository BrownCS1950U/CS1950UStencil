#pragma once

#include "core.h"

class Window
{
public:
    Window();
    ~Window();

private:
    void start();
    void loop();
    void end();
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    GLFWwindow* m_GLFWwindow;
    Core* m_core;
};