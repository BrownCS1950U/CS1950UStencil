#pragma once

#include "GLWrappers/vao.h"
#include "camera.h"
#include "GLWrappers/shader.h"
#include "material.h"
#include <map>
#include <iostream>
#include <GL/glew.h>
#include <memory>
#include <vector>

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void initialize();
    void clearScreen(GLbitfield mask);
    std::shared_ptr<Camera> getCamera();
    void addShader(std::string shaderName, std::vector<GLenum> shaderTypes, std::vector<const char*> filepaths);
    void removeShader(std::string shaderName);
    void bindShader(std::string shaderName = "default");
    void addShape(std::string shapeName, std::vector<float> data, VAOAttrib attribs);
    void removeShape(std::string shapeName);
    void drawShape(std::string shapeName);
    void addMaterial(std::string materialName, std::shared_ptr<Material> material);
    void removeMaterial(std::string materialName);
    void useMaterial(std::string materialName = "default");

    void initializeGLEW();

private:
    std::shared_ptr<Camera> m_camera;
    std::map<std::string, std::shared_ptr<Shader>> m_shaders;
    std::map<std::string, std::shared_ptr<VAO>> m_shapes;
    std::map<std::string, std::shared_ptr<Material>> m_materials;

    std::shared_ptr<Shader> m_active_shader;
};