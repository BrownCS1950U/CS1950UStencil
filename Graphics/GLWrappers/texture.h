#pragma once

#include "GL/glew.h"
#include <string>

#include "glm/glm.hpp"

#include "stb_image.h"

class Texture
{
public:
    Texture(glm::vec2 size, GLint internalFormat = GL_RGB, GLenum texTarget = GL_TEXTURE_2D, GLenum texUnit = GL_TEXTURE0);
    Texture(std::string filePath, GLint internalFormat = GL_RGB, GLenum texTarget = GL_TEXTURE_2D, GLenum texUnit = GL_TEXTURE0);
    ~Texture();

    void bind();
    void bind(GLenum texUnit);
    void unbind();
    void unbind(GLenum texUnit);
    GLuint getHandle();
    GLuint getTexUnit();

private:
    GLuint m_handle;
    GLenum m_texUnit;
    GLenum m_texTarget;
};