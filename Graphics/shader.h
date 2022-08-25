#pragma once

#include "shaderloader.h"

class Shader{
public:
    Shader(std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths);
    ~Shader();

    void bind();
    void unbind();

private:
    GLuint m_handle;
};