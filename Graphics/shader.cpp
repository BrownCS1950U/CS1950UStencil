#include "shader.h"

Shader::Shader(std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths){
    m_handle = ShaderLoader::createShaderProgram(shaderTypes, filepaths);  
}

Shader::~Shader(){
    glDeleteProgram(m_handle);
}

void Shader::bind(){
    glUseProgram(m_handle);
}

void Shader::unbind(){
    glUseProgram(0);
}