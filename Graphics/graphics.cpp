#include "graphics.h"

Graphics::Graphics(){
    m_camera = Camera();
}

Graphics::~Graphics(){

}

void Graphics::initializeGLEW(){
    glewExperimental = GL_TRUE;
    std::cout<<glewInit()<<std::endl;
}

void Graphics::clearScreen(GLbitfield mask){
    glClear(mask);
}

Camera& Graphics::getCamera(){
    return m_camera;
}

void Graphics::addShader(std::string shaderName, std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths){
    m_shaders.insert({shaderName, std::make_shared<Shader>(shaderTypes, filepaths)});
}

void Graphics::bindShader(std::string shaderName){
    m_shaders.at(shaderName)->bind();
}

void Graphics::addShape(std::string shapeName, std::vector<float> data, VAOAttrib attribs){
    m_shapes.insert({shapeName, std::make_shared<VAO>(std::make_shared<VBO>(data), attribs)});
}

void Graphics::drawShape(std::string shapeName){
    m_shapes.at(shapeName)->draw();
}