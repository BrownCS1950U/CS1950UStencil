#pragma once

#include "Graphics/global.h"

#include <GLFW/glfw3.h>

class Core
{
public:
    Core();
    ~Core();
    void update(double seconds);
    void draw(double timeSinceLastUpdate);
    void keyEvent(int key, int action);
    void mousePosEvent(double xpos, double ypos);
    void mouseButtonEvent(int button, int action);
    void windowResizeEvent(int width, int height);
    void framebufferResizeEvent(int width, int height);
};