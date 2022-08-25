#pragma once

#include "vao.h"
#include "camera.h"
#include "shader.h"
#include <map>

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void clearScreen(GLbitfield mask);
    Camera& getCamera();
    void addShader(std::string shaderName, std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths);
    void bindShader(std::string shaderName);
    void addShape(std::string shapeName, std::vector<float> data, VAOAttrib attribs);
    void drawShape(std::string shapeName);

    void initializeGLEW();

private:
    Camera m_camera;
    std::map<std::string, std::shared_ptr<Shader>> m_shaders;
    std::map<std::string, std::shared_ptr<VAO>> m_shapes;
};