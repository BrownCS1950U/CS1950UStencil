#pragma once

#include "global.h"

#include <GLFW/glfw3.h>

class Core
{
public:
    Core();
    ~Core();
    void update(float seconds);
    void keyEvent(int key, int action);
};