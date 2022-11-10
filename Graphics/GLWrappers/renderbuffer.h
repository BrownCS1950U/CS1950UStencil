#pragma once

#include <GL/glew.h>

#include "glm/glm.hpp"

class Renderbuffer
{
public:
    Renderbuffer(int width, int height);
    ~Renderbuffer();

    void bind();
    void unbind();
    GLuint getHandle();

private:
    GLuint m_handle;
};