#pragma once

#include <GL/glew.h>

#include "glm/glm.hpp"

class Renderbuffer
{
public:
    Renderbuffer(glm::vec2 size);
    ~Renderbuffer();

    void bind();
    void unbind();
    GLuint getHandle();

private:
    GLuint m_handle;
};