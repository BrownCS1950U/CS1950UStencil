#include "texture.h"
#include <iostream>

Texture::Texture(glm::vec2 size, GLint internalFormat, GLenum texTarget, GLenum texUnit):
    m_texTarget(texTarget),
    m_texUnit(texUnit)
{
    glGenTextures(1, &m_handle);
    bind();
    glTexParameteri(m_texTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_texTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(m_texTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(m_texTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexImage2D(m_texTarget, 0, internalFormat, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    unbind();
}

Texture::Texture(std::string filepath, GLint internalFormat, GLenum texTarget, GLenum texUnit):
    m_texTarget(texTarget),
    m_texUnit(texUnit)
{
    glGenTextures(1, &m_handle);
    bind();
    glTexParameteri(m_texTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(m_texTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(m_texTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(m_texTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    stbi_set_flip_vertically_on_load(1);
    int width, height, numChannels;
    unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &numChannels, 4);
    if (stbi_failure_reason()){
        std::cout << stbi_failure_reason() << std::endl;
    }
    glTexImage2D(m_texTarget, 0, internalFormat, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    stbi_image_free(data);
    unbind();
}

Texture::~Texture(){
    glDeleteTextures(1, &m_handle);
}

void Texture::bind(){
    glActiveTexture(m_texUnit);
    glBindTexture(m_texTarget, m_handle);
}

void Texture::bind(GLenum texUnit){
    glActiveTexture(texUnit);
    glBindTexture(m_texTarget, m_handle);
}

void Texture::unbind(){
    glActiveTexture(m_texUnit);
    glBindTexture(m_texTarget, 0);
}

void Texture::unbind(GLenum texUnit){
    glActiveTexture(texUnit);
    glBindTexture(m_texTarget, 0);
}

GLuint Texture::getHandle(){
    return m_handle;
}