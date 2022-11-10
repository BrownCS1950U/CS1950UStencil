#include "renderbuffer.h"

Renderbuffer::Renderbuffer(int width, int height){
    glGenRenderbuffers(1, &m_handle);
    bind();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    unbind();
}

Renderbuffer::~Renderbuffer(){
    glDeleteRenderbuffers(1, &m_handle);
}

void Renderbuffer::bind(){
    glBindRenderbuffer(GL_RENDERBUFFER, m_handle);
}

void Renderbuffer::unbind(){
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

GLuint Renderbuffer::getHandle(){
    return m_handle;
}