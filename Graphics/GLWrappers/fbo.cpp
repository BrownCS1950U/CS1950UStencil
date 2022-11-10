#include "fbo.h"

FBO::FBO(int width, int height):
    m_width(width),
    m_height(height)
{
    m_texture = std::make_shared<Texture>(m_width, m_height);
    m_renderbuffer = std::make_shared<Renderbuffer>(m_width, m_height);
    glGenFramebuffers(1, &m_handle);
    bind();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture->getHandle(), 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffer->getHandle());
    unbind();
}

FBO::~FBO(){
    glDeleteFramebuffers(1, &m_handle);
}

void FBO::bind(){
    glBindFramebuffer(GL_FRAMEBUFFER, m_handle);
    glViewport(0, 0, m_width, m_height);
}

void FBO::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 640, 480);
}

std::shared_ptr<Texture> FBO::getTexture(){
    return m_texture;
}