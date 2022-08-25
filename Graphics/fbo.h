#pragma once

#include <GL/glew.h>

#include "glm/glm.hpp"

#include <memory>
#include "texture.h"
#include "renderbuffer.h"

class FBO{
public:
    FBO(glm::vec2 size);
    ~FBO();
    void bind();
    void unbind();

private:
    GLuint m_handle;
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Renderbuffer> m_renderbuffer;
    glm::vec2 m_size;
};