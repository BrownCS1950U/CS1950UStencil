#include "fbo.h"

FBO::FBO(glm::vec2 size):
    m_size(size)
{
    m_texture = std::make_shared<Texture>(m_size);
    m_renderbuffer = std::make_shared<Renderbuffer>(m_size);
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
    glViewport(0, 0, m_size.x, m_size.y);
}

void FBO::unbind(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}