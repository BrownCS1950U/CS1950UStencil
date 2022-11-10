#pragma once

#include <GL/glew.h>

#include "glm/glm.hpp"

#include <memory>
#include "texture.h"
#include "renderbuffer.h"

class FBO{
public:
    FBO(int width, int height);
    ~FBO();
    void bind();
    void unbind();
    std::shared_ptr<Texture> getTexture();

private:
    GLuint m_handle;
    std::shared_ptr<Texture> m_texture;
    std::shared_ptr<Renderbuffer> m_renderbuffer;
    int m_width;
    int m_height;
};