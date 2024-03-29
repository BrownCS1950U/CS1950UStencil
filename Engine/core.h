#pragma once

#include "Graphics/global.h"

#include <GLFW/glfw3.h>

class Core
{
public:
    Core();
    ~Core();
    void update();
    void draw();
    void keyEvent(int key, int action);
    void mousePosEvent(double xpos, double ypos);
    void mouseButtonEvent(int button, int action);
    void scrollEvent(double distance);
    void windowResizeEvent(int width, int height);
    void framebufferResizeEvent(int width, int height);
};
